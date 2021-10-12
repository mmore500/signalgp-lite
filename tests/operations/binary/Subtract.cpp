#include "Catch/single_include/catch2/catch.hpp"

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

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up initial state

  // set up values to operate on in register
  core.registers[0] = 99;
  core.registers[1] = 7;

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 7, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  // expected: 99 - 7 == 92
  REQUIRE(core.registers == emp::array<float, 4>{99.f, 7.f, 99.f - 7.f, {}});
}
