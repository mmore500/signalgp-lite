#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/array.hpp"

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
  // ensure that we step through operations one-by-one
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 }; // eslint-disable-line no-eval
};

TEST_CASE("Test RegulatorGet") {
  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/RegulatorGet.json"
  });

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  cpu.GetActiveCore().registers[0] = 1.f;

  // check initial state
  REQUIRE(
    cpu.GetActiveCore().registers
    == emp::array<float, 4>{1.f, {}, {}, {}}
  );

  // execute single instruction
  sgpl::execute_cpu(1, cpu, program);

  // check final state (value is 0 by default)
  REQUIRE(
    cpu.GetActiveCore().registers
    == emp::array<float, 4>{0.f, {}, {}, {}}
  );

}
