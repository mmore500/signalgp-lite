#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/comparison/LessThan.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::LessThan>;
TEST_CASE("Test LessThan") {
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 };
};


  sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Less Than",
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
  const float operand1 = 3.f;
  const float operand2 = 97.f;

  sgpl::Core<spec_t> core( {operand1, operand2, -1, {}} );

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, 1, {}});

}

TEST_CASE("Test Not LessThan") {

  sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Less Than",
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
  const float operand1 = 97.f;
  const float operand2 = 3.f;

  sgpl::Core<spec_t> core( {operand1, operand2, -1, {}} );

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, 0, {}});

}
