#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/comparison/GreaterThan.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::GreaterThan>;

TEST_CASE("Test Not GreaterThan") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up false check

  // set up values to operate on in register
  core.registers[0] = 7;
  core.registers[1] = 99;
  core.registers[2] = -1; // will be overwritten

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{7, 99, -1, 0, 0, 0, 0, 0});
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 };
};


  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, 1, {}});

}

TEST_CASE("Test GreaterThan") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up values to operate on in register
  core.registers[0] = 99;
  core.registers[1] = 7;
  core.registers[2] = -1; // will be overwritten

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 7, -1, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, 0, {}});
}
