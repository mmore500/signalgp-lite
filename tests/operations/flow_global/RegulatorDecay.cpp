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
  sgpl::global::RegulatorDecay<>,
  sgpl::global::RegulatorSet<>,
  sgpl::global::RegulatorGet<>,
  sgpl::global::Anchor
>;

struct spec_t : public sgpl::Spec<library_t>{
  // ensure that we step through operations one-by-one
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 }; // eslint-disable-line no-eval
};

/**
 * RegulatorDecay should decay the regulator value
 * by the positive value passed to it
 * on the cycle following its call.
*/
TEST_CASE("Test RegulatorDecay, positive decay value") {
  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/RegulatorDecay.json"
  });

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  cpu.GetActiveCore().registers[0] = 99.f;

  // check initial state
  REQUIRE(
    cpu.GetActiveCore().registers
    == emp::array<float, 4>{99.f, {}, {}, {}}
  );

  // execute RegulatorSet
  REQUIRE(program[cpu.GetActiveCore().GetProgramCounter()].GetOpName() == "Set Global Regulator");
  sgpl::execute_cpu(1, cpu, program);

  // set register to a big number (amount to decay by)
  cpu.GetActiveCore().registers[1] = 9999999.f;

  REQUIRE(
    cpu.GetActiveCore().registers
    == emp::array<float, 4>{99.f, 9999999.f, {}, {}}
  );

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
  REQUIRE(
    cpu.GetActiveCore().registers
    == emp::array<float, 4>{0, 9999999.f, {}, {}}
  );

}

/**
 * RegulatorDecay should reverse-decay (i.e. increment)
 * the regulator value by the negative value passed to it
 * on the cycle following its call.
*/
TEST_CASE("Test RegulatorDecay, negative decay value") {
  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/RegulatorDecay.json"
  });

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  cpu.GetActiveCore().registers[0] = 99;

  // check initial state
  REQUIRE(
    cpu.GetActiveCore().registers
    == emp::array<float, 4>{99, {}, {}, {}}
  );

  // execute RegulatorSet
  sgpl::execute_cpu(1, cpu, program);

  // set register to a small number (amount to decay by)
  cpu.GetActiveCore().registers[1] = -9999999;

  REQUIRE(
    cpu.GetActiveCore().registers
    == emp::array<float, 4>{99, -9999999, {}, {}}
  );

  // execute RegulatorDecay
  sgpl::execute_cpu(1, cpu, program);

  // NOP (give a cycle for value to decay)
  sgpl::execute_cpu(1, cpu, program);

  // execute RegulatorGet
  sgpl::execute_cpu(1, cpu, program);

  // check to make sure value was decayed
  REQUIRE(
    cpu.GetActiveCore().registers
    == emp::array<float, 4>{99, -9999999, {}, {}}
  );

}
