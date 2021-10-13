#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/data/DataNode.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/unary/RandomDraw.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::RandomDraw>;
using spec_t = sgpl::Spec<library_t>;

/**
 * This testcase is intended to check the behavior of RandomDraw.
 * One hundred random RandomDraw operations are executed one hundred times each.
 * The total sums of each replicate are tallied, and the test only passes if the overall
 * standard deviation is sufficiently large (>1,000), the smallest sum is smaller than 10,
 * and the largest sum is greater than 100,000.
 */
TEST_CASE("Test RandomDraw") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  // define a datanode to keep track of sums of draws across replicates
  using data_node_t = emp::DataNode<
    double,
    emp::data::Current,
    emp::data::Range,
    emp::data::Stats
  >;
  data_node_t draw_sums;

  // define number of replicates
  constexpr size_t num_replicates = 100;
  for (size_t rep{}; rep < num_replicates; ++rep) {
    // create and initialize cpu
    sgpl::Cpu<spec_t> cpu;
    cpu.TryLaunchCore();

    // make a program of length 1
    const sgpl::Program<spec_t> program{1};
    // tell instruction to operate on 0th register
    program[0].args[0] = 0.f;

    double sum{};
    for (size_t draw{}; draw < 100; ++draw) {
      // execute instruction
      sgpl::execute_cpu(1, cpu, program);
      // store result (either true or false!)
      sum += cpu.GetActiveCore().registers[0];
    }

    draw_sums.Add(sum);
  }

  // check that standard deviation is sufficiently large
  // and that the max and min bounds are proper
  REQUIRE(draw_sums.GetStandardDeviation() > 1000.0);
  REQUIRE(draw_sums.GetMax() > 100000.0);
  REQUIRE(draw_sums.GetMin() < 10.0);
}
