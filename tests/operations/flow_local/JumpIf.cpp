#include "Catch/single_include/catch2/catch.hpp"

#include "../LoadProgram.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/operations/flow_local/JumpIf.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::Nop<1>, sgpl::local::Anchor, sgpl::local::JumpIf>;
using spec_t = sgpl::Spec<library_t>;

TEST_CASE("Test true JumpIf") {
  sgpl::Program<spec_t> program = sgpl::test::LoadProgram<spec_t>("JumpIf");

  // create peripheral
  spec_t::peripheral_t peripheral;

  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  // set up values to operate on in register
  core.registers[0] = true;

  // set up what registers to operate on
  program[0].args[0] = 0;

  // check initial state
  REQUIRE(core.GetProgramCounter() == 0);

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // make sure we jumped
  REQUIRE(core.GetProgramCounter() != 1);
}


TEST_CASE("Test false JumpIf") {
  sgpl::Program<spec_t> program;

  std::ifstream is("assets/JumpIf.json") = sgpl::test::LoadProgram<spec_t>("JumpIf");

  sgpl::Core<spec_t> core;

  // create peripheral
  spec_t::peripheral_t peripheral;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  // set up values to operate on in register
  core.registers[0] = false;

  // set up what registers to operate on
  program[0].args[0] = 0;

  // check initial state
  REQUIRE(core.GetProgramCounter() == 0);

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // make sure we didn't jump
  REQUIRE(core.GetProgramCounter() == 1);
}
