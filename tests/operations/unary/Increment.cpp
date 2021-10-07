#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/unary/Increment.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::Increment>;
using spec_t = sgpl::Spec<library_t>;

auto make_program() {
  sgpl::Program<spec_t> program;

  std::stringstream ss(R"(
    {
      "value0": [
          {
              "operation": "Increment",
              "args": {
                  "value0": 0,
                  "value1": 0,
                  "value2": 0
              },
              "bitstring": "0000000000000000000000000000000000000000000000000000000000000000",
              "descriptors": []
          }
      ]
    }
  )");

  cereal::JSONInputArchive archive( ss );
  archive( program );

  return program;
}

TEST_CASE("Test Increment") {

  sgpl::Program<spec_t> program = make_program();

  sgpl::Core<spec_t> core;

  // set up false check

  // set up values to operate on in register
  core.registers[0] = 99;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 8>{100, 0, 0, 0, 0, 0, 0, 0});

}
