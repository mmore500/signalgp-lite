#include "Catch/single_include/catch2/catch.hpp"

#include "../LoadProgram.hpp"

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
using spec_t = sgpl::Spec<library_t>;

TEST_CASE("Test RegulatorGet") {
  sgpl::Program<spec_t> program = sgpl::test::LoadProgram<spec_t>("RegulatorGet");

  // create peripheral
  spec_t::peripheral_t peripheral;

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  cpu.GetActiveCore().registers[0] = 1;

  // check initial state
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{1, 0, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::execute_cpu(1, cpu, program, peripheral);

  // check final state (value is 0 by default)
  REQUIRE(cpu.GetActiveCore().registers ==  emp::array<float, 8>{0, 0, 0, 0, 0, 0, 0, 0});

}
