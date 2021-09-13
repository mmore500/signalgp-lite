#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/operations/actions/Nop.hpp"
#include "sgpl/operations/flow_global/flow_global.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/EmptyType.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<
  sgpl::Nop<0>,
  sgpl::global::RegulatorAdj<>,
  sgpl::global::RegulatorSet<>,
  sgpl::global::RegulatorGet<>,
  sgpl::global::Anchor
>;

struct spec_t : public sgpl::Spec<library_t>{
  // this is here so that we can step through the operations properly
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
};

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test RegulatorAdj") {
  sgpl::Program<spec_t> program;

  std::ifstream is("assets/RegulatorAdj.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

  is.close();

  sgpl::Cpu<spec_t> cpu;

  cpu.InitializeAnchors(program);

  REQUIRE(cpu.TryLaunchCore());

  cpu.GetActiveCore().registers[0] = 99;

  // check initial state
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute RegulatorSet
  REQUIRE(program[cpu.GetActiveCore().GetProgramCounter()].GetOpName() == "Set Global Regulator");
  sgpl::execute_cpu(1, cpu, program, peripheral);

  // set register to a big number (amount to adjust by)
  cpu.GetActiveCore().registers[1] = 100000;

  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{99, 100000, 0, 0, 0, 0, 0, 0});

  // execute RegulatorAdj
  REQUIRE(program[cpu.GetActiveCore().GetProgramCounter()].GetOpName() == "Adjust Global Regulator");
  sgpl::execute_cpu(1, cpu, program, peripheral);

  // NOP
  REQUIRE(program[cpu.GetActiveCore().GetProgramCounter()].GetOpName() == "Nop-0");
  sgpl::execute_cpu(1, cpu, program, peripheral);

  // execute RegulatorGet
  REQUIRE(program[cpu.GetActiveCore().GetProgramCounter()].GetOpName() == "Get Global Regulator");
  sgpl::execute_cpu(1, cpu, program, peripheral);

  // check to make sure value was adjusted
  REQUIRE(cpu.GetActiveCore().registers == emp::array<float, 8>{100099, 100000, 0, 0, 0, 0, 0, 0});
}
