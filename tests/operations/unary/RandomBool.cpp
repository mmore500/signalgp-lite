#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "conduit/include/uitsl/polyfill/bit_cast.hpp"

#include "Empirical/include/emp/data/DataNode.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/operations/unary/RandomBool.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

using library_t = sgpl::OpLibrary<sgpl::RandomBool>;
struct spec_t : public sgpl::Spec<library_t>{
  // this is here so that we can step through the operations properly
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // at least 20 cores are required
  static constexpr inline size_t num_cores{ 20 }; // eslint-disable-line no-eval
};

TEST_CASE("Test RandomBool") {
  // define number of replicates
  const size_t replicates = 100;

  // create peripheral
  typename spec_t::peripheral_t peripheral;

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  emp::DataNode<size_t, emp::data::Current, emp::data::Range, emp::data::Stats> data;

  // get 100 random bools
  for (size_t i{}; i < replicates; i++) {
    // create and initialize cpu
    sgpl::Cpu<spec_t> cpu;
    for (size_t i{}; i < 20; ++i) cpu.TryLaunchCore();

    // make a program of length 1
    sgpl::Program<spec_t> program{1};
    // tell instruction to operate on 0th register
    program[i].args[0] = 0;

    size_t replicate_count{};
    for (size_t j{}; j < 100; j++) {
      // execute instruction
      sgpl::execute_cpu(1, cpu, program, peripheral);
      // store result (either true or false!)
      replicate_count += cpu.GetActiveCore().registers[0];
    }

    data.Add(replicate_count);
  }

  // check that result is within 25 "trues" of 50%
  // this means that the instruction is (sufficiently) random
  std::cout << data.GetStandardDeviation() << std::endl;
  std::cout << data.GetMin() << " " << data.GetMax() << std::endl;

}
