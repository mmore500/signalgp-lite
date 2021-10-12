#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/comparison/LogicalOr.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::LogicalOr>;
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 };
};

TEST_CASE("Test LogicalOr, both operands true") {

  sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Logical Or",
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

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, true, {}});

}


TEST_CASE("Test LogicalOr, one operand true and one false") {

  sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Logical Or",
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
  const float operand2 = false;

  sgpl::Core<spec_t> core( {operand1, operand2, -1, {}} );

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, true, {}});

}

TEST_CASE("Test LogicalOr, both operands false") {

  sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Logical Or",
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
  const float operand1 = false;
  const float operand2 = false;

  sgpl::Core<spec_t> core( {operand1, operand2, -1, {}} );

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, false, {}});

}
