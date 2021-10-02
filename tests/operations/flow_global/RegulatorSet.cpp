#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_global/flow_global.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<
  sgpl::global::RegulatorSet<>,
  sgpl::global::RegulatorGet<>,
  sgpl::global::Anchor
>;

struct spec_t : public sgpl::Spec<library_t>{
  // this is here so that we can step through the operations properly
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
};

TEST_CASE("Test RegulatorSet") {
  sgpl::Program<spec_t> program = sgpl::test::LoadProgram<spec_t>("RegulatorSet");

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  cpu.GetActiveCore().registers[0] = 99;

  // check initial state
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute RegulatorSet
  REQUIRE(program[cpu.GetActiveCore().GetProgramCounter()].GetOpName() == "Set Global Regulator");
  sgpl::execute_cpu(1, cpu, program);

  // clear register
  cpu.GetActiveCore().registers[0] = 0;

  // check that registers were cleared
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{0, 0, 0, 0, 0, 0, 0, 0});

  // execute RegulatorGet
  REQUIRE(program[cpu.GetActiveCore().GetProgramCounter()].GetOpName() == "Get Global Regulator");
  sgpl::execute_cpu(1, cpu, program);

  // check to make sure value was retrieved
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

}
