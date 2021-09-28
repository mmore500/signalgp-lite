#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/operations/unary/Not.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::Not>;
using spec_t = sgpl::Spec<library_t>;

TEST_CASE("Test Not") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up false check

  // set up values to operate on in register
  core.registers[0] = 99;

  // set up what registers to operate on
  program[0].args[0] = 0;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check final state
  REQUIRE(core.registers == emp::array<float, 8>{0, 0, 0, 0, 0, 0, 0, 0});

}
