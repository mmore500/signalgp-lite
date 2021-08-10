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

        int fit_count = 0;

        // evaluate fitness four times to weed out RNG
        for (size_t i = 0; i < 4; ++i) {

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

            fit_count += (peripheral.output == answer);

        }
        return fit_count == 4;
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

    auto get_max_fitness = [&ea_world]() -> std::pair<double, Organism> {
        double max_fitness = 0;
        const Organism* most_fit = nullptr;

        for (size_t i = 0; i < ea_world.GetSize(); i++) {
            const double curr_fitness = ea_world[i].GetFitness();
            if (curr_fitness > max_fitness) {
                max_fitness = curr_fitness;
                most_fit = &ea_world[i];
            }
        }

        return {max_fitness, *most_fit};
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

    auto do_nopout = [](Organism& org) -> size_t {
        std::cout << "###### Initiating NopOut ######\n";

        const size_t prog_length = org.program.size();
        const double initial_fitness = org.GetFitness();

        std::cout << "Program length: " << prog_length << "\n";
        std::cout << "Initial fitness: " << initial_fitness << std::endl;

        // number of times we nopped out an instruction that mattered
        size_t inutile_count = 0;

        // for every instruction in the program...
        for (size_t i = 0; i < prog_length; ++i) {
            // ...make a backup of the program...
            const auto curr_program = org.program;

            std::cout << "nopping out " << i << "\n";
            // ...nop out instruction...
            org.program[i].NopOut();

            // ...and reevaluate fitness.
            const double new_fitness = org.GetFitness();

            std::cout << "new fitness: " << new_fitness << "\n";

            // if fitness has changed,
            if (initial_fitness != new_fitness) {
                // then this instruction matters, so roll back the program
                org.program = curr_program;
            }
            else {
                // otherwise, count it as inutile
                inutile_count++;
            }
        }

        return inutile_count;
    };

    auto nopout_until_fully_utile = [&do_nopout](Organism& org) {
        size_t inutile_count = 0;
        do {
            inutile_count = do_nopout(org);
            std::cout << " ##### Ineffectual count: " << inutile_count << "#####" << std::endl;
        } while (inutile_count);
    };

    for (size_t t = 0; t < config.UPDATES(); ++t) {
        // loop normally
        print_fitness(t);
        ea_world.DoMutations();
        LexicaseSelect(ea_world, GetFitFuns(), PopulationSize);
        ea_world.Update();

        // check for early exit
        auto res = get_max_fitness();

        std::cout << "Max fitness: " << res.first << std::endl;

        if (res.first >= config.THRESHOLD_FITNESS()) {
            Organism organism = res.second;
            organism.program.Print(std::cout);

            do_nopout(organism);

            organism.program.Print(std::cout);

            break;
        }
    }

    print_fitness();
}
