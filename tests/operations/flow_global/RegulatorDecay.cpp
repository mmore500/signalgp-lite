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
  sgpl::global::RegulatorDecay<>,
  sgpl::global::RegulatorSet<>,
  sgpl::global::RegulatorGet<>,
  sgpl::global::Anchor
>;

struct spec_t : public sgpl::Spec<library_t>{
  // this is here so that we can step through the operations properly
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
};

/**
 * RegulatorDecay should decay the regulator value
 * by the positive value passed to it
 * on the cycle following its call.
*/
TEST_CASE("Test Positive RegulatorDecay") {
  sgpl::Program<spec_t> program = sgpl::test::LoadProgram<spec_t>("RegulatorDecay");

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  cpu.GetActiveCore().registers[0] = 99;

  // check initial state
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute RegulatorSet
  REQUIRE(program[cpu.GetActiveCore().GetProgramCounter()].GetOpName() == "Set Global Regulator");
  sgpl::execute_cpu(1, cpu, program);

  // set register to a big number (amount to decay by)
  cpu.GetActiveCore().registers[1] = 9999999;

  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{99, 9999999, 0, 0, 0, 0, 0, 0});

  // execute RegulatorDecay
  REQUIRE(program[cpu.GetActiveCore().GetProgramCounter()].GetOpName() == "Decay Global Regulator");
  sgpl::execute_cpu(1, cpu, program);

  // NOP (Anchor)
  REQUIRE(program[cpu.GetActiveCore().GetProgramCounter()].GetOpName() == "Global Anchor");
  sgpl::execute_cpu(1, cpu, program);

  // execute RegulatorGet
  REQUIRE(program[cpu.GetActiveCore().GetProgramCounter()].GetOpName() == "Get Global Regulator");
  sgpl::execute_cpu(1, cpu, program);

  // check to make sure value was decayed
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{0, 9999999, 0, 0, 0, 0, 0, 0});

}

/**
 * RegulatorDecay should reverse-decay (i.e. increment)
 * the regulator value by the negative value passed to it
 * on the cycle following its call.
*/
TEST_CASE("Test Negative RegulatorDecay") {
  sgpl::Program<spec_t> program = sgpl::test::LoadProgram<spec_t>("RegulatorDecay");

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  cpu.GetActiveCore().registers[0] = 99;

  // check initial state
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute RegulatorSet
  sgpl::execute_cpu(1, cpu, program);

  // set register to a small number (amount to decay by)
  cpu.GetActiveCore().registers[1] = -9999999;

  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{99, -9999999, 0, 0, 0, 0, 0, 0});

  // execute RegulatorDecay
  sgpl::execute_cpu(1, cpu, program);

  // NOP (give a cycle for value to decay)
  sgpl::execute_cpu(1, cpu, program);

  // execute RegulatorGet
  sgpl::execute_cpu(1, cpu, program);

  // check to make sure value was decayed
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{99, -9999999, 0, 0, 0, 0, 0, 0});

}
