#include <iostream>
#include <ratio>
#include <string>

#include "Empirical/include/emp/math/Random.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/library/OpLibraryCoupler.hpp"
#include "sgpl/library/prefab/ControlFlowOpLibrary.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

emp::Random rng;

// custom hardware peripheral, can be written to or read from during execution
struct Peripheral {
  size_t greet_count{};
  std::string name;
};

// custom CPU operation
struct SayHello {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>&,
    const sgpl::Instruction<Spec>&,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t& peripheral
  ) {
    std::cout << "for the " << peripheral.greet_count++ << "th time... ";
    std::cout << "hello there " << peripheral.name << '\n';
  }

  static std::string name() { return "SayHello"; }

  static size_t prevalence() { return 1; }

};

// extends prefab ControlFlowOpLibrary with SayHello operation
using library_t = sgpl::OpLibraryCoupler<sgpl::ControlFlowOpLibrary, SayHello>;

// custom compile-time configurator type
using spec_t = sgpl::Spec<library_t, Peripheral>;

int main() {

  sgpl::Cpu<spec_t> cpu;
  Peripheral peripheral;
  peripheral.name = "Grace Hopper";

  sgpl::Program<spec_t> program{ 100 }; // randomly generated, 100 instructions

  cpu.InitializeAnchors( program ); // load program onto CPU

  // generate random signals to launch available virtual cores
  while ( cpu.TryLaunchCore( emp::BitSet<64>(rng) ) ) ;

  // execute up to one thousand instructions
  sgpl::execute_cpu<spec_t>( std::kilo::num, cpu, program, peripheral );

}
