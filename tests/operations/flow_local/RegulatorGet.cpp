#include "Catch/single_include/catch2/catch.hpp"

#include "../LoadProgram.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_local/RegulatorGet.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<
  sgpl::local::Anchor,
  sgpl::local::RegulatorGet
>;
using spec_t = sgpl::Spec<library_t>;

TEST_CASE("Test RegulatorGet") {
  sgpl::Program<spec_t> program = sgpl::test::LoadProgram<spec_t>("RegulatorGet");

  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  core.registers[0] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{1, 0, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state (value is 0 by default)
  REQUIRE(core.registers == emp::array<float, 8>{0, 0, 0, 0, 0, 0, 0, 0});

}
