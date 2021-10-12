#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/bit_cast.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/bitwise/BitwiseNot.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::BitwiseNot>;
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 };
};

TEST_CASE("Test BitwiseNot") {

  sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Bitwise Not",
          "args": {
            "value0": 1,
            "value1": 0,
            "value2": 0
          },
          "bitstring": "0000000000000000000000000000000000000000000000000000000000000000",
          "descriptors": []
        }
      ]
    }
  )");

  // define value constants
  const float operand1 = std::bit_cast<float>(0b00000000000000000000000001001001);
  const float result = std::bit_cast<float>(0b11111111111111111111111110110110);

  sgpl::Core<spec_t> core( {operand1, {}, {}, {}} );

  // execute single instruction
  sgpl::advance_core(core, program);

  std::cout << std::bitset<8>(core.registers[1]) << std::endl;

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, result, {}, {}});
}
