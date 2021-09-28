#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/operations/actions/TerminateIf.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::TerminateIf, sgpl::Nop<0>>;
using spec_t = sgpl::Spec<library_t>;

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test TerminateIf") {

  sgpl::Program<spec_t> program;

  std::ifstream is("assets/TrueTerminateIf.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

  sgpl::Core<spec_t> core;

  // set register to true
  core.registers[0] = true;

  // tell terminateif to check inside the 0th register
  program[0].args[0] = 0;

  // check initial state
  REQUIRE(!core.HasTerminated());

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check final state
  REQUIRE(core.HasTerminated());
}


TEST_CASE("Test False TerminateIf") {

  sgpl::Program<spec_t> program;

  std::ifstream is("assets/FalseTerminateIf.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

  sgpl::Core<spec_t> core;

  // check initial state
  REQUIRE(!core.HasTerminated());

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check that it didn't terminate
  REQUIRE(!core.HasTerminated());
}
