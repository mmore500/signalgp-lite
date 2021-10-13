#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/array.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/binary/Subtract.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::Subtract>;
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 };
};

TEST_CASE("Test Subtract") {

  const sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Subtract",
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

  // set up values to subtract in register
  sgpl::Core<spec_t> core( {99.f, 7.f, {}, {}} );

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  // expected: 99 - 7 == 92
  REQUIRE(core.registers == emp::array<float, 4>{99.f, 7.f, 99.f - 7.f, {}});
}
