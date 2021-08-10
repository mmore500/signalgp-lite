#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/operations/bitwise/CountOnes.hpp"

#include "sgpl/hardware/Core.hpp"
#include "sgpl/program/Program.hpp"

#include "sgpl/algorithm/execute_core.hpp"

#include "sgpl/spec/Spec.hpp"

#include "sgpl/utility/EmptyType.hpp"

#include "conduit/include/uitsl/polyfill/bit_cast.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::CountOnes>;

using spec_t = sgpl::Spec<library_t>;

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test CountOnes") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up initial state
  const float val1 = std::bit_cast<float>(0b001101);

  // set up values to operate on in register
  core.registers[0] = val1;

  // set up what registers to operate on
  program[0].args[0] = 1;
  program[0].args[1] = 0;

  // check initial state
  REQUIRE_THAT(core.registers, Catch::Matchers::Equals(
    emp::array<float, 8>{val1, 0, 0, 0, 0, 0, 0, 0}
  ));

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check final state
  REQUIRE_THAT(core.registers, Catch::Matchers::Equals(
    emp::array<float, 8>{val1, 3, 0, 0, 0, 0, 0, 0}
  ));
}
