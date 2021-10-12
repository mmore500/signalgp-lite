#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/unary/Decrement.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typdefs
using library_t = sgpl::OpLibrary<sgpl::Decrement>;
struct spec_t : public sgpl::Spec<library_t>{
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 };
};

auto make_program() {
  sgpl::Program<spec_t> program;

  std::stringstream ss(R"(
    {
      "value0": [
          {
              "operation": "Decrement",
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

TEST_CASE("Test Decrement") {
  sgpl::Program<spec_t> program = make_program();

  sgpl::Core<spec_t> core;

  // set up values to operate on in register
  core.registers = emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0};

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{98, 0, 0, 0});


}
