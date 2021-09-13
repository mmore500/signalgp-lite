#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "conduit/include/uitsl/polyfill/bit_cast.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/operations/bitwise/BitwiseOr.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"


// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::BitwiseOr>;
using spec_t = sgpl::Spec<library_t>;

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test BitwiseOr") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up initial state
  const float val1 = std::bit_cast<float>(0b001001);
  const float val2 = std::bit_cast<float>(0b100101);
  const float val3 = std::bit_cast<float>(0b101101);

  std::cout << val1 << " " << val2 << " " << val3 << std::endl;

  // set up values to operate on in register
  core.registers[0] = val1;
  core.registers[1] = val2;

  // set up what registers to operate on
  program[0].args[0] = 2;
  program[0].args[1] = 0;
  program[0].args[2] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{val1, val2, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check final state
  REQUIRE(core.registers == emp::array<float, 8>{val1, val2, val3, 0, 0, 0, 0, 0});
}
