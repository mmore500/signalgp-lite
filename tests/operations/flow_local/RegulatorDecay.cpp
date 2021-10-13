#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/array.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_local/RegulatorDecay.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<
  sgpl::local::Anchor,
  sgpl::local::RegulatorDecay,
  sgpl::local::RegulatorGet,
  sgpl::local::RegulatorSet
>;
struct spec_t : public sgpl::Spec<library_t>{
  // ensure that we step through the operations one-by-one
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 }; // eslint-disable-line no-eval
};

TEST_CASE("Test RegulatorDecay, positive value") {
  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/RegulatorDecay.json"
  });

  sgpl::Core<spec_t> core({99.f, {}, {}, {}});

  // load all anchors manually
  core.LoadLocalAnchors(program);

  // execute RegulatorSet
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Set Local Regulator"
  );
  sgpl::advance_core(core, program);

  // set register to a big number (amount to decay by)
  core.registers[1] = 9999999.f;

  REQUIRE(core.registers == emp::array<float, 4>{99.f, 9999999.f, {}, {}});

  // execute RegulatorDecay
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Decay Local Regulator"
  );
  sgpl::advance_core(core, program);

  // NOP
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Nop-0"
  );
  sgpl::advance_core(core, program);

  // execute RegulatorGet
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Get Local Regulator"
  );
  sgpl::advance_core(core, program);

  // check to make sure value was decayed
  REQUIRE(core.registers == emp::array<float, 4>{0.f, 9999999.f, {}, {}});

}

TEST_CASE("Test RegulatorDecay, negative value (forestalls decay)") {
  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/RegulatorDecay.json"
  });

  sgpl::Core<spec_t> core({99.f, {}, {}, {}});

  // load all anchors manually
  core.LoadLocalAnchors(program);

  // execute RegulatorSet
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Set Local Regulator"
  );
  sgpl::advance_core(core, program);

  // set register to a small number (amount to anti-decay by)
  core.registers[1] = ;

  REQUIRE(core.registers == emp::array<float, 4>{99.f, -9999999.f, {}, {}});

  // execute RegulatorDecay
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Decay Local Regulator"
  );
  sgpl::advance_core(core, program);

  // NOP
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Nop-0"
  );
  sgpl::advance_core(core, program);

  // execute RegulatorGet
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Get Local Regulator"
  );
  sgpl::advance_core(core, program);

  // check to make sure value was protected from decay
  REQUIRE(core.registers == emp::array<float, 4>{99.f, -9999999.f, {}, {}});

}
