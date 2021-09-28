#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/operations/flow_local/JumpIfNot.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::Nop<1>, sgpl::local::Anchor, sgpl::local::JumpIfNot>;
using spec_t = sgpl::Spec<library_t>;

TEST_CASE("Test false JumpIfNot") {
  sgpl::Program<spec_t> program;

  std::ifstream is("assets/JumpIfNot.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

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

  // make sure we jumped
  REQUIRE(core.GetProgramCounter() != 1);
}


TEST_CASE("Test true JumpIfNot") {
  sgpl::Program<spec_t> program;

  std::ifstream is("assets/JumpIfNot.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

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

  // make sure we didn't jump
  REQUIRE(core.GetProgramCounter() == 1);
}
