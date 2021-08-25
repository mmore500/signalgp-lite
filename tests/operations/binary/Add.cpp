#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/operations/binary/Add.hpp"

#include "sgpl/hardware/Core.hpp"
#include "sgpl/program/Program.hpp"

#include "sgpl/algorithm/execute_core.hpp"

#include "sgpl/spec/Spec.hpp"

#include "sgpl/utility/EmptyType.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::Add>;

using spec_t = sgpl::Spec<library_t>;

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test Add") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up initial state

  // set up values to add in register
  core.registers[0] = 1;
  core.registers[1] = 2;

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 1;

  // check initial state
  REQUIRE_THAT(core.registers, Catch::Matchers::Equals(
    emp::array<float, 8>{1, 2, 0, 0, 0, 0, 0, 0}
  ));

  for (auto reg : core.registers) std::cout << reg << " ";
  std::cout << std::endl;

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check final state
  REQUIRE_THAT(core.registers, Catch::Matchers::Equals(
    emp::array<float, 8>{1, 2, 3, 0, 0, 0, 0, 0}
  ));

  for (auto reg : core.registers) std::cout << reg << " ";
  std::cout << std::endl;
}
