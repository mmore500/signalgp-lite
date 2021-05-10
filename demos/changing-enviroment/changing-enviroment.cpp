#include <algorithm>
#include <iostream>
#include <limits>

#include "../third-party/Empirical/include/emp/config/ArgManager.hpp"
#include "../third-party/Empirical/include/emp/math/Random.hpp"
#include "../third-party/Empirical/include/emp/Evolve/World.hpp"

#include "../include/sgpl/spec/Spec.hpp"
#include "../include/sgpl/library/prefab/CompleteOpLibrary.hpp"
#include "../include/sgpl/hardware/Cpu.hpp"
#include "../include/sgpl/program/Program.hpp"
#include "../include/sgpl/algorithm/execute_cpu.hpp"
#include "../include/sgpl/utility/ThreadLocalRandom.hpp"
#include "../include/sgpl/library/OpLibraryCoupler.hpp"

#include "config.hpp"

static Config config{};

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
};

using library_t = sgpl::OpLibraryCoupler<sgpl::CompleteOpLibrary, SetState>;

// TODO: override spec and change line 34 to ratio<1,2>
using spec_t = sgpl::Spec<library_t, Peripheral>;

using tag_t = spec_t::tag_t;

struct Organism {
    mutable Peripheral peripheral;

    mutable sgpl::Cpu<spec_t> cpu;

    mutable sgpl::Program<spec_t> program{256};

    Organism() : Organism(0) { ; }
    Organism(int t) : peripheral(t) {
        cpu.InitializeAnchors(program);
        while (cpu.TryLaunchCore(tag_t(sgpl::tlrand.Get())));
    }

    double GetFitness() const {
        // initialize tag lookup with K random tags
        const static std::vector<tag_t> lookup = [](){
            std::vector<tag_t> ret;
            ret.reserve(config.ENVIROMENT_STATES());
            std::generate_n(
                std::back_inserter(ret),
                config.ENVIROMENT_STATES(),
                [](){ return tag_t(sgpl::tlrand.Get()); }
            );
            return ret;
        }();

        // minimum fitness
        int min_fitness = std::numeric_limits<int>::max();

        // three trials
        for (size_t i = 0; i < 3; ++i)
        {
            int trial_fitness = 0;

            // reinitialize CPU
            cpu.InitializeAnchors(program);

            // ...where each trial comprised 256 time steps.
            for (size_t t = 0; t < 256; ++t)
            {
                // ...an agent’s fitness was equal to
                // the number of timesteps in which its internal state
                // matched the environment state during evaluation.

                // set enviroment to tag
                const size_t index = t % config.ENVIROMENT_STATES();
                cpu.TryLaunchCore(lookup[index]);

                // execute up to 1k instructions
                sgpl::execute_cpu<spec_t>(std::hecto::num, cpu, program, peripheral);

                if (peripheral.output == index) trial_fitness++;
            }
            // After three trials, an agent’s fitness was equal
            // to the minimum fitness value obtained across its three trials.
            min_fitness = std::min(trial_fitness, min_fitness);
        }
        return static_cast<double>(min_fitness);
    }
    bool DoMutations(emp::Random&) {
        program.ApplyPointMutations( 0.0002f );

        program.ApplySequenceMutations(config);

        return true;
    }

    bool operator== (const Organism& rhs) { return peripheral.output == rhs.peripheral.output; }
    bool operator!= (const Organism& rhs) { return !operator==(rhs); }
    bool operator< (const Organism& rhs) { return peripheral.output < rhs.peripheral.output; }

};

int main(int argc, char* argv[]) {

    // make argmanager specs from config
    auto specs = emp::ArgManager::make_builtin_specs(&config);

    emp::ArgManager arg_manager{argc, argv, specs};

    arg_manager.UseCallbacks();

    // print config
    config.Write(std::cout);

std::cout << "\nPost-Tourney Size = " << ea_world.GetSize() << std::endl;
for (size_t i = 0; i < ea_world.GetSize(); i++) std::cout << ea_world[i].GetFitness() << " ";
std::cout << std::endl;

}