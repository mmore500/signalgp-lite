#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/bit_cast.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/bitwise/BitwiseOr.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::BitwiseOr>;
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 };
};

TEST_CASE("Test BitwiseOr") {

  sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Bitwise Or",
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

  // set up value constants
  const float operand1 = std::bit_cast<float>(0b001001);
  const float operand2 = std::bit_cast<float>(0b100101);
  const float val3 = std::bit_cast<float>(0b101101);

  std::cout << val1 << " " << val2 << " " << val3 << std::endl;
  sgpl::Core<spec_t> core( {operand1, operand2, {}, {}} );

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, val3, {}});
}
