#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/bit_cast.hpp"
#include "Empirical/include/emp/data/DataNode.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/bitwise/RandomFill.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::RandomFill>;
using spec_t = sgpl::Spec<library_t>;

/**
 * RandomFill fills the 32 bits that represent a float with bits
 * randomly chosen from a uniform distribution. This test checks this
 * behavior by making sure that every bit gets set to both 0 and 1 at least once.
 */
TEST_CASE("Test RandomFill") {
  // number of replicates
  constexpr size_t replicates = 1000;

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  int and_ed{};
  int or_ed{};

  for (size_t rep{}; rep < replicates; rep++) {
    // create and initialize cpu
    sgpl::Cpu<spec_t> cpu;
    cpu.TryLaunchCore();

    // make a program of length 1
    sgpl::Program<spec_t> program{1};
    // tell instruction to operate on 0th register
    program[0].args[0] = 0;
    // execute instruction
    sgpl::execute_cpu(1, cpu, program);

    and_ed &= std::bit_cast<int>(cpu.GetActiveCore().registers[0]);
    or_ed |= std::bit_cast<int>(cpu.GetActiveCore().registers[0]);
  }

  // check that every bit as been a 1 and a 0 at least once
  // we do this by ANDing and ORing every result
  // at the end, and_ed should just be zeros, and or_ed should just be ones
  // and that the max and min bounds are proper
  REQUIRE(and_ed == 0);
  REQUIRE(or_ed == -1); // in two's compliment, -1 is represented by setting all bits to 1
}
