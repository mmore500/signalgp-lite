#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>

#include "../third-party/Empirical/include/emp/config/ArgManager.hpp"
#include "../third-party/Empirical/include/emp/datastructs/hash_utils.hpp"
#include "../third-party/Empirical/include/emp/Evolve/World.hpp"
#include "../third-party/Empirical/include/emp/math/Random.hpp"


#include "../include/sgpl/algorithm/execute_cpu.hpp"
#include "../include/sgpl/hardware/Cpu.hpp"
#include "../include/sgpl/library/OpLibraryCoupler.hpp"
#include "../include/sgpl/program/Program.hpp"
#include "../include/sgpl/spec/Spec.hpp"
#include "../include/sgpl/utility/ThreadLocalRandom.hpp"

#include "config.hpp"

#include "ToggleRegulationOpLibrary.hpp"

const size_t PopulationSize = 1000;

struct Peripheral {
    int output{};

    Peripheral() : output(-1) { ; }
    Peripheral(int x) : output(x) { ; }
};

struct SetState {
    template<typename Spec>
    static void run(
        sgpl::Core<Spec>& core,
        const sgpl::Instruction<Spec>& inst,
        const sgpl::Program<Spec>&,
        typename Spec::peripheral_t& peripheral
    ) {
        using tag_t = typename Spec::tag_t;
        // hash instruction bitset tag, mod it by # of possible responses, and set this output to that
        tag_t tag = inst.GetTag();

        size_t hash = std::hash<tag_t>{}(tag);

        peripheral.output = hash % prevalence();
    }

    static std::string name() { return "SetState"; }

    static size_t prevalence() { return config.ENVIROMENT_STATES(); }

    template<typename Spec>
    static auto descriptors( const sgpl::Instruction<Spec>& inst ) {
        using tag_t = typename Spec::tag_t;
        tag_t tag = inst.GetTag();
        size_t hash = std::hash<tag_t>{}(tag);

        return std::map<std::string, std::string>{
            { "state idx", emp::to_string( static_cast<int>( hash % prevalence() ) ) }
        };
    }
};

using library_t = sgpl::OpLibraryCoupler<sgpl::ToggleRegulationOpLibrary, SetState>;

// TODO: override spec and change line 34 to ratio<1,2>
using spec_t = sgpl::Spec<library_t, Peripheral>;

using tag_t = spec_t::tag_t;

struct Organism {
    using program_t = sgpl::Program<spec_t>;

    mutable Peripheral peripheral;

    mutable sgpl::Cpu<spec_t> cpu;

    mutable program_t program{256};

    Organism() : Organism(0) { ; }
    Organism(int t) : peripheral(t) {
        cpu.InitializeAnchors(program);
        while (cpu.TryLaunchCore(tag_t(sgpl::tlrand.Get())));
    }

    bool Evaluate(const size_t first, const size_t second) const {
        // vector of possible input signals
        const static std::vector<tag_t> signals = [](){
            std::vector<tag_t> ret;
            ret.reserve(config.ENVIROMENT_STATES());
            std::generate_n(
                std::back_inserter(ret),
                config.ENVIROMENT_STATES(),
                [](){ return tag_t(sgpl::tlrand.Get()); }
            );
            return ret;
        }();

        // reinitialize CPU
        cpu.Reset();
        cpu.InitializeAnchors(program);

        // launch cpu with first tag
        cpu.TryLaunchCore(signals[first]);

        // execute up to 128 instructions
        sgpl::execute_cpu<spec_t>(128, cpu, program, peripheral);

        // launch cpu with second tag
        cpu.TryLaunchCore(signals[second]);

        // execute up to 128 instructions
        sgpl::execute_cpu<spec_t>(128, cpu, program, peripheral);

        // if correct response is observed, increment fitness
        const size_t answer = (first + second) % config.NUMBER_RESPONSES();
        return peripheral.output == answer;
    }

    double GetFitness() const {
        const static emp::vector<size_t> states = [](){
            emp::vector<size_t> ret(config.ENVIROMENT_STATES());

            std::iota(ret.begin(), ret.end(), 0);

            return ret;
        }();

        // minimum fitness
        int fitness = 0;

        // iterate through all pairs of states
        for (const size_t i : states) {
            for (const size_t j : states) {
                fitness += Evaluate(i, j);
            }
        }

        return static_cast<double>(fitness);
    }
    bool DoMutations(emp::Random&) {
        program.ApplyMutations(config);
        return true;
    }

    bool operator==(const Organism& rhs) { return peripheral.output == rhs.peripheral.output; }
    bool operator!=(const Organism& rhs) { return !operator==(rhs); }
    bool operator<(const Organism& rhs) { return peripheral.output < rhs.peripheral.output; }

};

auto GetFitFuns() {
    emp::vector< std::function<double(const Organism&)> > fit_funs;

    std::generate_n(
        std::back_inserter(fit_funs),
        config.ENVIROMENT_STATES() * config.ENVIROMENT_STATES(),
        [&](){
            return [i = fit_funs.size()](const Organism& org){
                return static_cast<double>(org.Evaluate(
                    i / config.ENVIROMENT_STATES(),
                    i % config.ENVIROMENT_STATES()
                ));
            };
        }
    );

    return fit_funs;
}

int main(int argc, char* argv[]) {
    // make argmanager specs from config
    auto specs = emp::ArgManager::make_builtin_specs(&config);

    emp::ArgManager arg_manager{argc, argv, specs};

    arg_manager.UseCallbacks();

    // print config
    config.Write(std::cout);

    // reseed random number generator
    sgpl::tlrand.Reseed(config.SEED());

    emp::World<Organism> ea_world;
    ea_world.SetPopStruct_Mixed(true);

    if (config.LOGGING()) ea_world.SetupFitnessFile(
        emp::to_string(config.LOGGING_FILENAME(), ".csv")
    );

    for (int i = 0; i < PopulationSize; i++) ea_world.Inject(i);

    auto get_max_fitness = [&ea_world]() -> double {
        double max_fitness = 0;
        for (size_t i = 0; i < ea_world.GetSize(); i++) max_fitness = std::max(ea_world[i].GetFitness(), max_fitness);
        return max_fitness;
    };

    auto get_best_fit_individual = [&ea_world]() -> Organism {
        // select best-fit individual
        std::multimap<double, size_t> fit_map;
        for (size_t id = 0; id < ea_world.GetSize(); id++) {
            if (ea_world.IsOccupied(id)) {
                const double cur_fit = ea_world.CalcFitnessID(id);
                fit_map.insert( std::make_pair(cur_fit, id) );
            }
        }

        // Grab the top fitnesses and move them into the next generation.
        auto m = fit_map.rbegin();

        const size_t repro_id = m->second;
        return ea_world.GetGenomeAt(repro_id);
    };

    auto print_fitness = [&ea_world, get_best_fit_individual](const size_t time = -1){
        if (time != -1) std::cout << "Update: " << time << std::endl;
        //for (size_t i = 0; i < ea_world.GetSize(); i++) std::cout << ea_world[i].GetFitness() << " ";
        //std::cout << std::endl;
        //std::cout << "Best fitness: " << get_best_fit_individual().GetFitness() << std::endl;
        //std::cout << std::endl;
    };

    for (size_t t = 0; t < config.UPDATES(); ++t) {
        // loop normally
        print_fitness(t);
        ea_world.DoMutations();
        LexicaseSelect(ea_world, GetFitFuns(), PopulationSize);
        ea_world.Update();

        // check for early exit
        const double max_fitness = get_max_fitness();
        if (max_fitness >- config.THRESHOLD_FITNESS()) break;
    }

    print_fitness();
}
