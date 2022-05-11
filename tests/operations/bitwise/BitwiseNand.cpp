#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/bit_cast.hpp"
#include "Empirical/include/emp/base/array.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/bitwise/BitwiseNand.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::BitwiseNand>;
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 }; // eslint-disable-line no-eval
};

TEST_CASE("Test BitwiseNand") {

  const sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Bitwise Nand",
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
  const auto operand1 = std::bit_cast<float>(
    0b11111110111111101111111011111110
  );
  const auto operand2 = std::bit_cast<float>(
    0b11010101110101011101010111010101
  );
  const auto expected_result = std::bit_cast<float>(
    ~(0b11111110111111101111111011111110 & 0b11010101110101011101010111010101)
  );

  // set up initial values to AND in register
  sgpl::Core<spec_t> core( {operand1, operand2, {}, {}} );

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(
    core.registers
    == emp::array<float, 4>{operand1, operand2, expected_result, {}}
  );
}
