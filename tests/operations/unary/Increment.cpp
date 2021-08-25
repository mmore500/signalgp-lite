#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/operations/unary/Increment.hpp"


#include "sgpl/hardware/Core.hpp"
#include "sgpl/program/Program.hpp"

#include "sgpl/algorithm/execute_core.hpp"

#include "sgpl/spec/Spec.hpp"

#include "sgpl/utility/EmptyType.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::Increment>;

using spec_t = sgpl::Spec<library_t>;

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test Increment") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up false check

  // set up values to operate on in register
  core.registers[0] = 99;

  // set up what registers to operate on
  program[0].args[0] = 0;

  // check initial state
  REQUIRE_THAT(core.registers, Catch::Matchers::Equals(
    emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0}
  ));

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check final state
  REQUIRE_THAT(core.registers, Catch::Matchers::Equals(
    emp::array<float, 8>{100, 0, 0, 0, 0, 0, 0, 0}
  ));

}
