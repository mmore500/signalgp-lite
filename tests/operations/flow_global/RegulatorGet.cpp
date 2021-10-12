#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_global/flow_global.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<
  sgpl::global::RegulatorGet<>,
  sgpl::global::Anchor
>;
struct spec_t : public sgpl::Spec<library_t>{
  // this is here so that we can step through the operations properly
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 };
};

TEST_CASE("Test RegulatorGet") {
  sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/RegulatorGet.json"
  });

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  cpu.GetActiveCore().registers[0] = 1;

  // check initial state
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 4>{1, 0, 0, 0});

  // execute single instruction
  sgpl::execute_cpu(1, cpu, program);

  // check final state (value is 0 by default)
  REQUIRE(cpu.GetActiveCore().registers ==  emp::array<float, 4>{0, 0, 0, 0});

}
