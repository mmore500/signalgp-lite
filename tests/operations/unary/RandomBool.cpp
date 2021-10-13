#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/bit_cast.hpp"
#include "Empirical/include/emp/data/DataNode.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/unary/RandomBool.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

using library_t = sgpl::OpLibrary<sgpl::RandomBool>;
struct spec_t : public sgpl::Spec<library_t>{
  // ensure that we step through operations one-by-one
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
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
  data_node_t successful_flips;

  for (size_t rep{}; rep < replicates; ++rep) {
    // create and initialize cpu
    sgpl::Cpu<spec_t> cpu;
    cpu.TryLaunchCore();

    // make a program of length 1
    const sgpl::Program<spec_t> program(R"(
      {
        "value0": [
          {
            "operation": "Generate Random Bool",
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

    size_t cur_replicate_successes{};
    for (size_t flip_count{}; flip_count < 100; ++flip_count) {
      // execute instruction
      sgpl::execute_cpu(1, cpu, program);
      // store result (either true or false!)
      cur_replicate_successes += cpu.GetActiveCore().registers[0];
    }

    successful_flips.Add(cur_replicate_successes);
  }

  // check that result is within 25 "trues" of 50%
  // this means that the instruction is (sufficiently) random
  REQUIRE(successful_flips.GetMean() < 75);
  REQUIRE(25 < successful_flips.GetMean());
  REQUIRE(successful_flips.GetMin() < 25);
  REQUIRE(successful_flips.GetMax() > 75);

}
