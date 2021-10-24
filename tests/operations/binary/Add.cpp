#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/array.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/binary/Add.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::Add>;
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 }; // eslint-disable-line no-eval
};

TEST_CASE("Test Add") {

  const sgpl::Program<spec_t> program(R"(
    {
      "value0": [
        {
          "operation": "Add",
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

  // set up values to add in register
  sgpl::Core<spec_t> core( {1.f, 2.f, {}, {}} );

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  // expected: 1 + 2 == 3
  REQUIRE(core.registers == emp::array<float, 4>{1.f, 2.f, 1.f + 2.f, {}});
}
