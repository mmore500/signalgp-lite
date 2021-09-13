#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/operations/flow_global/JumpIf.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/EmptyType.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::Nop<1>, sgpl::global::Anchor, sgpl::global::JumpIf>;

struct spec_t : public sgpl::Spec<library_t>{
  // this is here so that we can step through the operations properly
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
};

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test true JumpIf") {
  sgpl::Program<spec_t> program;

  std::ifstream is("assets/JumpIf.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

  is.close();

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  // set up values to operate on in register
  cpu.GetActiveCore().registers[0] = true;

  // set up what registers to operate on
  program[0].args[0] = 0;

  // check initial state
  REQUIRE(cpu.GetActiveCore().GetProgramCounter() == 0);

  // execute single instruction
  sgpl::execute_cpu(1, cpu, program, peripheral);

  // // make sure we jumped
  REQUIRE(cpu.GetActiveCore().GetProgramCounter() != 1);
}


TEST_CASE("Test false JumpIf") {
  sgpl::Program<spec_t> program;

  std::ifstream is("assets/JumpIf.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

  is.close();

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  // set up values to operate on in register
  cpu.GetActiveCore().registers[0] = false;

  // set up what registers to operate on
  program[0].args[0] = 0;

  // check initial state
  REQUIRE(cpu.GetActiveCore().GetProgramCounter() == 0);

  // execute single instruction
  sgpl::execute_cpu(1, cpu, program, peripheral);

  // make sure we didnt jump
  REQUIRE(cpu.GetActiveCore().GetProgramCounter() == 1);
}
