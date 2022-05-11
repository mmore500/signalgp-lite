#include <iostream>

#include "../third-party/Empirical/include/emp/math/Random.hpp"

#include "../include/sgpl/algorithm/execute_cpu.hpp"
#include "../include/sgpl/hardware/Cpu.hpp"
#include "../include/sgpl/library/OpLibraryCoupler.hpp"
#include "../include/sgpl/library/prefab/CompleteOpLibrary.hpp"
#include "../include/sgpl/program/Program.hpp"
#include "../include/sgpl/spec/Spec.hpp"
#include "../include/sgpl/utility/ThreadLocalRandom.hpp"

struct PrintMessage {
  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    std::cout << "Hello world!" << std::endl;
  }

  static std::string name() { return "PrintMessage"; }

  static size_t prevalence() { return 10; }

};

using library_t = sgpl::OpLibraryCoupler<sgpl::CompleteOpLibrary, PrintMessage>;

using spec_t = sgpl::Spec<library_t>;

int main() {

  sgpl::Cpu<spec_t> cpu;

  sgpl::Program<spec_t> program{10};

  cpu.InitializeAnchors(program);

  while (cpu.TryLaunchCore(emp::BitSet<64>(sgpl::tlrand.Get())));

  sgpl::execute_cpu<spec_t>(std::kilo::num, cpu, program);
}
