#include <iostream>

#include "../third-party/Empirical/include/emp/math/Random.hpp"
#include "../third-party/Empirical/include/emp/Evolve/World.hpp"

#include "../include/sgpl/spec/Spec.hpp"
#include "../include/sgpl/library/prefab/CompleteOpLibrary.hpp"
#include "../include/sgpl/hardware/Cpu.hpp"
#include "../include/sgpl/program/Program.hpp"
#include "../include/sgpl/algorithm/execute_cpu.hpp"
#include "../include/sgpl/utility/ThreadLocalRandom.hpp"
#include "../include/sgpl/library/OpLibraryCoupler.hpp"

struct Peripheral {
  int output{};
};

struct Identity {
    template<typename Spec>
    static void run(
        sgpl::Core<Spec>& core,
        const sgpl::Instruction<Spec>& inst,
        const sgpl::Program<Spec>&,
        typename Spec::peripheral_t& peripheral
    ) {
        // hash instruction bitset tag, mod it by # of possible responses, and set this output to that
        peripheral.output = core.registers[0];
    }

    static std::string name() { return "Identity"; }

    static size_t prevalence() { return 10; }
};

using library_t = sgpl::OpLibraryCoupler<sgpl::CompleteOpLibrary, Identity>;

using spec_t = sgpl::Spec<library_t, Peripheral>;

struct Organism {
    mutable Peripheral per;

    mutable sgpl::Cpu<spec_t> cpu;

    mutable sgpl::Program<spec_t> program{100};

    Organism() : Organism(0) { ; }
    Organism(int t) : per(t) {
        cpu.InitializeAnchors(program);
        while (cpu.TryLaunchCore(emp::BitSet<64>(sgpl::tlrand.Get())));
    }

    double GetFitness() const {
        cpu.InitializeAnchors(program);
        while (cpu.TryLaunchCore(emp::BitSet<64>(sgpl::tlrand.Get())));

        sgpl::execute_cpu<spec_t>(std::kilo::num, cpu, program, per);

        return per.output;
    }
    bool DoMutations(emp::Random&) {
        program.ApplyPointMutations( 0.005f );
        return true;
    }

    std::weak_ordering operator<=> (const Organism& rhs) {
        return per.output <=> rhs.per.output;
    }
};

int main() {

  emp::World<Organism> ea_world;
  ea_world.SetPopStruct_Mixed(true);

  for (int i = 0; i < 100; i++) ea_world.Inject(i);

  std::cout << "\nStart Size = " << ea_world.GetSize() << std::endl;
  for (size_t i = 0; i < ea_world.GetSize(); i++) std::cout << ea_world[i].GetFitness() << " ";
  std::cout << std::endl;

  for (int i = 0; i < 100; i++) {
    ea_world.DoMutations();
    TournamentSelect(ea_world, 7, 100);
    ea_world.Update();
    for (size_t i = 0; i < ea_world.GetSize(); i++) std::cout << ea_world[i].GetFitness() << " ";
  }

std::cout << "\nPost-Tourney Size = " << ea_world.GetSize() << std::endl;
for (size_t i = 0; i < ea_world.GetSize(); i++) std::cout << ea_world[i].GetFitness() << " ";
std::cout << std::endl;

}