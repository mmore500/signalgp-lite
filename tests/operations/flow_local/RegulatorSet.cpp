#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/operations/flow_local/RegulatorSet.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::local::RegulatorSet, sgpl::local::RegulatorGet, sgpl::local::Anchor>;
using spec_t = sgpl::Spec<library_t>;

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test RegulatorSet") {
  sgpl::Program<spec_t> program;

  std::ifstream is("assets/RegulatorSet.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  core.registers[0] = 99;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute RegulatorSet
  sgpl::advance_core(core, program, peripheral);

  // clear register
  core.registers[0] = 0;

  // check that registers were cleared
  REQUIRE(core.registers == emp::array<float, 8>{0, 0, 0, 0, 0, 0, 0, 0});

  // execute RegulatorGet
  sgpl::advance_core(core, program, peripheral);

  // check to make sure value was retrieved
  REQUIRE(core.registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

}
