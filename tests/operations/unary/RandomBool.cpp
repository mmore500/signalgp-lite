#include <algorithm>

#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/bit_cast.hpp"
#include "Empirical/include/emp/data/DataNode.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/unary/RandomBool.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/CountingIterator.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

using library_t = sgpl::OpLibrary<sgpl::RandomBool>;
struct spec_t : public sgpl::Spec<library_t>{
  // ensure that we step through operations one-by-one
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 1 }; // eslint-disable-line no-eval
};

/**
 * This testcase is intended to check the behavior of RandomBool.
 * One hundred random RandomBool operations are executed one hundred times each.
 * The `true` results are tallied, and the test only passes if the overall
 * mean, max, and min of successful flips is between 25% and 75%.
 */
TEST_CASE("Test RandomBool") {
  // define number of replicates
  constexpr size_t replicates = 100;

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  // define datanode to track the successful "coin flip" (50/50) counts
  using data_node_t = emp::DataNode<
    size_t,
    emp::data::Current,
    emp::data::Range,
    emp::data::Stats
  >;
  data_node_t replicate_counts;

  for (size_t rep{}; rep < replicates; ++rep) {
    // create and initialize cpu
    sgpl::Cpu<spec_t> cpu;
    cpu.TryLaunchCore();

    // randomly generate a program of length 1
    // we only have 1 register,
    // so all random bool operations will write into register 0
    const sgpl::Program<spec_t> program(1);

    const double cur_replicate_successes = std::accumulate(
      sgpl::CountingIterator{},
      sgpl::CountingIterator{100ul},
      size_t{},
      [&cpu, &program](const auto accumulator, const auto&){
        sgpl::execute_cpu(1, cpu, program);
        return accumulator + cpu.GetActiveCore().registers[0];
      }
    );

    replicate_counts.Add(cur_replicate_successes);
  }

  // check that result is within 25 "trues" of 50%
  // this means that the instruction is (sufficiently) random
  REQUIRE(
    std::clamp(
        replicate_counts.GetMean(),
        25.0,
        75.0
    ) == replicate_counts.GetMean()
  );
  REQUIRE(replicate_counts.GetMin() < 25);
  REQUIRE(replicate_counts.GetMax() > 75);

}
