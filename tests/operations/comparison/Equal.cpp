#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/operations/comparison/Equal.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/EmptyType.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::Equal>;

using spec_t = sgpl::Spec<library_t>;

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test Not Equal") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up false check

  // set up values to operate on in register
  core.registers[0] = 99;
  core.registers[1] = 7;
  core.registers[2] = -1; // random int

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 7, -1, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check final state
  REQUIRE(core.registers == emp::array<float, 8>{99, 7, 0, 0, 0, 0, 0, 0});

}

TEST_CASE("Test Equal") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up values to operate on in register
  core.registers[0] = 99;
  core.registers[1] = 7;
  core.registers[2] = -1; // random int

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 0;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 7, -1, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check final state
  REQUIRE(core.registers == emp::array<float, 8>{99, 7, 1, 0, 0, 0, 0, 0});

}
