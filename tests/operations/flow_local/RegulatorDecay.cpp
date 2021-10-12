#include "Catch/single_include/catch2/catch.hpp"

#include "../LoadProgram.hpp"

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
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 };
};


  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  core.registers[0] = 99;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 4>{99, 0, 0, 0});

  // execute RegulatorSet
  sgpl::advance_core(core, program);

  // set register to a big number (amount to decay by)
  core.registers[1] = 9999999;

  REQUIRE(core.registers == emp::array<float, 4>{99, 9999999, 0, 0});

  // execute RegulatorDecay
  sgpl::advance_core(core, program);

  // NOP
  sgpl::advance_core(core, program);

  // execute RegulatorGet
  sgpl::advance_core(core, program);

  // check to make sure value was decayed
  REQUIRE(core.registers == emp::array<float, 4>{0, 9999999, 0, 0});

}

TEST_CASE("Test Negative RegulatorDecay") {
  sgpl::Program<spec_t> program = sgpl::test::LoadProgram<spec_t>("RegulatorDecay");

  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  core.registers[0] = 99;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 4>{99, 0, 0, 0});

  // execute RegulatorSet
  sgpl::advance_core(core, program);

  // set register to a small number (amount to decay by)
  core.registers[1] = -9999999;

  REQUIRE(core.registers == emp::array<float, 4>{99, -9999999, 0, 0});

  // execute RegulatorDecay
  sgpl::advance_core(core, program);

  // NOP
  sgpl::advance_core(core, program);

  // execute RegulatorGet
  sgpl::advance_core(core, program);

  // check to make sure value was decayed
  REQUIRE(core.registers == emp::array<float, 4>{99, -9999999, 0, 0});

}
