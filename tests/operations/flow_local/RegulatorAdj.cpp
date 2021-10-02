#include "Catch/single_include/catch2/catch.hpp"

#include "../LoadProgram.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_local/RegulatorAdj.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::local::RegulatorAdj, sgpl::local::RegulatorSet, sgpl::local::RegulatorGet, sgpl::local::Anchor>;
using spec_t = sgpl::Spec<library_t>;

TEST_CASE("Test RegulatorAdj") {
  sgpl::Program<spec_t> program = sgpl::test::LoadProgram<spec_t>("RegulatorAdj");

  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  core.registers[0] = 99;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute RegulatorSet
  sgpl::advance_core(core, program);

  // set register to a big number (amount to decay by)
  core.registers[1] = 100000;

  REQUIRE(core.registers == emp::array<float, 8>{99, 100000, 0, 0, 0, 0, 0, 0});

  // execute RegulatorAdj
  sgpl::advance_core(core, program);

  // NOP
  sgpl::advance_core(core, program);

  // execute RegulatorGet
  sgpl::advance_core(core, program);

  // check to make sure value was decayed
  REQUIRE(core.registers == emp::array<float, 8>{100099, 100000, 0, 0, 0, 0, 0, 0});

}
