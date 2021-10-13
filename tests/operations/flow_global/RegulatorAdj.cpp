#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/array.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/actions/Nop.hpp"
#include "sgpl/operations/flow_global/flow_global.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<
  sgpl::Nop<>,
  sgpl::global::Anchor,
  sgpl::global::RegulatorAdj<>,
  sgpl::global::RegulatorGet<>,
  sgpl::global::RegulatorSet<>
>;
struct spec_t : public sgpl::Spec<library_t>{
  // ensure that we step through operations one-by-one
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 }; // eslint-disable-line no-eval
};

TEST_CASE("Test RegulatorAdj") {
  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/RegulatorAdj.json"
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
  REQUIRE(
    program[cpu.GetActiveCore().GetProgramCounter()].GetOpName()
    == "Set Global Regulator"
  );
  sgpl::execute_cpu(1, cpu, program);

  // set register to a big number (amount to adjust by)
  cpu.GetActiveCore().registers[1] = 100000.f;

  REQUIRE(
    cpu.GetActiveCore().registers
    == emp::array<float, 4>{99.f, 100000.f, {}, {}}
  );

  // execute RegulatorAdj
  REQUIRE(
    program[cpu.GetActiveCore().GetProgramCounter()].GetOpName()
    == "Adjust Global Regulator"
  );
  sgpl::execute_cpu(1, cpu, program);

  // NOP (give a cycle for regulator to be adjusted)
  REQUIRE(
    program[cpu.GetActiveCore().GetProgramCounter()].GetOpName()
    == "Nop-0"
  );
  sgpl::execute_cpu(1, cpu, program);

  // execute RegulatorGet
  REQUIRE(
    program[cpu.GetActiveCore().GetProgramCounter()].GetOpName()
    == "Get Global Regulator"
  );
  sgpl::execute_cpu(1, cpu, program);

  // check to make sure value was adjusted
  REQUIRE(
    cpu.GetActiveCore().registers
    == emp::array<float, 4>{100099.f, 100000.f, {}, {}}
  );
}
