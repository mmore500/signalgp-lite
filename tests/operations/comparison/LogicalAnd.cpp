#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/comparison/LogicalAnd.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::LogicalAnd>;
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 };
};

TEST_CASE("Test LogicalAnd, both operands true") {

  sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Logical And",
          "args": {
            "value0": 2,
            "value1": 0,
            "value2": 1
          },
          "bitstring": "0000000000000000000000000000000000000000000000000000000000000000",
          "descriptors": []
        }
      ]
    }
  )");

  // define value constants
  const float operand1 = true;
  const float operand2 = true;

  sgpl::Core<spec_t> core( {operand1, operand2, -1, {}} );

TEST_CASE("Test true LogicalAnd") {

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, true, {}});

}

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up values to operate on in register
  core.registers[0] = true;
  core.registers[1] = true;

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{true, true, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, false, {}});

}

TEST_CASE("Test false LogicalAnd") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up values to operate on in register
  core.registers[0] = true;
  core.registers[1] = false;

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{true, false, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, false, {}});

}