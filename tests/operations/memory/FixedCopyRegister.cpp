#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/bit_cast.hpp"
#include "Empirical/include/emp/base/array.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/memory/FixedCopyRegister.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::FixedCopyRegister>;
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 }; // eslint-disable-line no-eval
};

TEST_CASE("Test FixedCopyRegister") {

  const sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Fixed Copy Register",
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
  constexpr float operand1 = 1021251.f;

  // set up initial values to copy in register
  sgpl::Core<spec_t> core( {operand1, {}, {}, {}} );

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(
    core.registers
    == emp::array<float, 4>{operand1, operand1, {}, {}}
  );
}
