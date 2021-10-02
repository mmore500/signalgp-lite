#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/bit_cast.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/bitwise/BitwiseShift.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::BitwiseShift>;
using spec_t = sgpl::Spec<library_t>;

TEST_CASE("Test Left BitwiseShift") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up initial state

  // set up values to operate on in register
  core.registers[0] = std::bit_cast<float>(0b001001);
  core.registers[1] = 3.0;

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{std::bit_cast<float>(0b001001), 3.0, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 8>{std::bit_cast<float>(0b001001), 3.0, std::bit_cast<float>(0b001001000), 0, 0, 0, 0, 0});
}


TEST_CASE("Test Right BitwiseShift") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up initial state

  // set up values to operate on in register
  core.registers[0] = std::bit_cast<float>(0b001001);
  core.registers[1] = -3.0;

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{std::bit_cast<float>(0b001001), -3.0, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 8>{std::bit_cast<float>(0b001001), -3.0, std::bit_cast<float>(0b000001), 0, 0, 0, 0, 0});
}
