#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "conduit/include/uitsl/polyfill/bit_cast.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/operations/unary/RandomBool.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

using library_t = sgpl::OpLibrary<sgpl::RandomBool>;
struct spec_t : public sgpl::Spec<>{
  // this is here so that we can step through the operations properly
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // at least 20 cores are required
  static constexpr inline size_t num_cores{ 20 }; // eslint-disable-line no-eval
};

auto map_to_unit = [](const typename spec_t::tag_t& tag) -> double {

  constexpr double max_double = spec_t::tag_t::MaxDouble();

  return tag.GetDouble() / max_double;

};

TEST_CASE("Test RandomBool") {
  // define number of replicates
  const size_t replicates = 100;

  // create peripheral
  typename spec_t::peripheral_t peripheral;

  sgpl::Program<spec_t> program{replicates};

  sgpl::Cpu<spec_t> cpu;

  // initialize cpu
  for (size_t i{}; i < 20; ++i) cpu.TryLaunchCore();

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  // check initial state
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{0, 0, 0, 0, 0, 0, 0, 0});


  size_t count{};
  // get 100 random bools
  for (size_t i{}; i < replicates; i++) {
    // set instruction's tag to max_double * 0.5
    // this is so that RandomBool returns true with exactly 0.5 probability.
    program[i].tag.SetUInt64(
       0,
       static_cast<uint64_t>(spec_t::tag_t::MaxDouble() * 0.5)
    );

    std::cout << "test: " << map_to_unit(
      program[i].tag
    ) << std::endl;
    std::cout << std::endl;

    std::cout << cpu.GetActiveCore().GetProgramCounter() << " ";
    // tell instruction to operate on 0th register
    program[i].args[0] = 0;
    // execute instruction
    sgpl::execute_cpu(1, cpu, program, peripheral);
    std::cout << cpu.GetActiveCore().GetProgramCounter() << std::endl;

    // store result (either true or false!)
    count += cpu.GetActiveCore().registers[0];
  }

  // check that result is within 25 "trues" of 50%
  // this means that the instruction is (sufficiently) random
  REQUIRE(count > 25);
  REQUIRE(count < 75);

}
