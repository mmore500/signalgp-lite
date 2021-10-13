#include <algorithm>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/data/DataNode.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/unary/RandomDraw.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/CountingIterator.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::RandomDraw>;
struct spec_t : public sgpl::Spec<library_t>{
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 1 }; // eslint-disable-line no-eval
};

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
  data_node_t replicate_sums;

  // define number of replicates
  constexpr size_t num_replicates = 100;
  for (size_t rep{}; rep < num_replicates; ++rep) {
    // create and initialize cpu
    sgpl::Cpu<spec_t> cpu;
    cpu.TryLaunchCore();

    // randomly generate a program of length 1
    // we only have 1 register,
    // so all random bool operations will write into register 0
    const sgpl::Program<spec_t> program{1};

    const double sum_over_draws = std::accumulate(
      sgpl::CountingIterator{},
      sgpl::CountingIterator{100ul},
      double{},
      [&cpu, &program](const auto accumulator, const auto&){
        sgpl::execute_cpu(1, cpu, program);
        return accumulator + cpu.GetActiveCore().registers[0];
      }
    );

    replicate_sums.Add(sum_over_draws);
  }

  // check that standard deviation is sufficiently large
  // and that the max and min bounds are proper
  REQUIRE(replicate_sums.GetStandardDeviation() > 1000.0);
  REQUIRE(replicate_sums.GetMax() > 100000.0);
  REQUIRE(replicate_sums.GetMin() < 10.0);
}
