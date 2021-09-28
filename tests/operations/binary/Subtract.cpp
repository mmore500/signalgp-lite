#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/operations/binary/Subtract.hpp"
#include "sgpl/program/Program.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::Subtract>;
using spec_t = sgpl::Spec<library_t>;

TEST_CASE("Test Subtract") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // create peripheral
  spec_t::peripheral_t peripheral;

  // set up initial state

  // set up values to operate on in register
  core.registers[0] = 99;
  core.registers[1] = 7;

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 7, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check final state
  // expected: 99 - 7 == 92
  REQUIRE(core.registers == emp::array<float, 8>{99, 7, 92, 0, 0, 0, 0, 0});
}
