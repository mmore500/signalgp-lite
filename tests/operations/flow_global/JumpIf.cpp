#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_global/JumpIf.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<
  sgpl::Nop<1>,
  sgpl::global::Anchor,
  sgpl::global::JumpIf
>;
struct spec_t : public sgpl::Spec<library_t> {
  // this is here so that we can step through the operations properly
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
};

TEST_CASE("Test Global JumpIf, true value") {
  sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/JumpIf.json"
  });

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  // set up values to operate on in register
  cpu.GetActiveCore().registers[0] = true;

  // check initial state
  REQUIRE(cpu.GetActiveCore().GetProgramCounter() == 0);

  // execute single instruction
  sgpl::execute_cpu(1, cpu, program);

  // // make sure we jumped
  REQUIRE(cpu.GetActiveCore().GetProgramCounter() != 1);
}


TEST_CASE("Test Global JumpIf, false value") {
  sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/JumpIf.json"
  });

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  // set up values to operate on in register
  cpu.GetActiveCore().registers[0] = false;

  // check initial state
  REQUIRE(cpu.GetActiveCore().GetProgramCounter() == 0);

  // execute single instruction
  sgpl::execute_cpu(1, cpu, program);

  // make sure we did not jump
  REQUIRE(cpu.GetActiveCore().GetProgramCounter() == 1);
}
