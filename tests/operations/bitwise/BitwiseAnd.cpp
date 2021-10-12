#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/bit_cast.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/bitwise/BitwiseAnd.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::BitwiseAnd>;
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 };
};

TEST_CASE("Test BitwiseAnd") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up initial state
  const float val1 = std::bit_cast<float>(0b11010110);
  const float val2 = std::bit_cast<float>(0b10010101);
  const float val3 = std::bit_cast<float>(0b10010100);

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
  sgpl::advance_core(core, program);

  std::cout << sizeof(float) * 8 << std::endl;
  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, operand2, result, {}});
}
