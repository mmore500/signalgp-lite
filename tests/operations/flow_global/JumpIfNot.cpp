#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "../LoadProgram.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/operations/flow_global/JumpIfNot.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::Nop<1>, sgpl::global::Anchor, sgpl::global::JumpIfNot>;

struct spec_t : public sgpl::Spec<library_t>{
  // this is here so that we can step through the operations properly
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
};

TEST_CASE("Test false JumpIfNot") {
  sgpl::Program<spec_t> program = sgpl::test::LoadProgram<spec_t>("JumpIfNot");

  // create peripheral
  spec_t::peripheral_t peripheral;

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

  // make sure we jumped
  REQUIRE(cpu.GetActiveCore().GetProgramCounter() != 1);
}


TEST_CASE("Test true JumpIfNot") {
  sgpl::Program<spec_t> program;

  std::ifstream is("assets/JumpIfNot.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

  // create peripheral
  spec_t::peripheral_t peripheral;

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  // load all anchors manually
  cpu.GetActiveCore().LoadLocalAnchors(program);

  // set up values to operate on in register
  cpu.GetActiveCore().registers[0] = true;

  // set up what registers to operate on
  program[0].args[0] = 0;

  // check initial state
  REQUIRE(cpu.GetActiveCore().GetProgramCounter() == 0);

  // execute single instruction
  sgpl::execute_cpu(1, cpu, program, peripheral);

  // make sure we didn't jump
  REQUIRE(cpu.GetActiveCore().GetProgramCounter() == 1);
}
