#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/operations/flow_local/RegulatorDecay.hpp"

#include "sgpl/hardware/Core.hpp"
#include "sgpl/program/Program.hpp"

#include "sgpl/algorithm/execute_core.hpp"

#include "sgpl/spec/Spec.hpp"

#include "sgpl/utility/EmptyType.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::local::RegulatorDecay, sgpl::local::RegulatorSet, sgpl::local::RegulatorGet, sgpl::local::Anchor>;

using spec_t = sgpl::Spec<library_t>;

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test Positive RegulatorDecay") {
  sgpl::Program<spec_t> program;

  std::ifstream is("assets/RegulatorDecay.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

  is.close();

  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  core.registers[0] = 99;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute RegulatorSet
  sgpl::advance_core(core, program, peripheral);

  // set register to a big number (amount to decay by)
  core.registers[1] = 9999999;

  REQUIRE(core.registers == emp::array<float, 8>{99, 9999999, 0, 0, 0, 0, 0, 0});

  // execute RegulatorDecay
  sgpl::advance_core(core, program, peripheral);

  // NOP
  sgpl::advance_core(core, program, peripheral);

  // execute RegulatorGet
  sgpl::advance_core(core, program, peripheral);

  // check to make sure value was decayed
  REQUIRE(core.registers == emp::array<float, 8>{0, 9999999, 0, 0, 0, 0, 0, 0});

}

TEST_CASE("Test Negative RegulatorDecay") {
  sgpl::Program<spec_t> program;

  std::ifstream is("assets/RegulatorDecay.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

  is.close();

  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  core.registers[0] = 99;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute RegulatorSet
  sgpl::advance_core(core, program, peripheral);

  // set register to a small number (amount to decay by)
  core.registers[1] = -9999999;

  REQUIRE(core.registers == emp::array<float, 8>{99, -9999999, 0, 0, 0, 0, 0, 0});

  // execute RegulatorDecay
  sgpl::advance_core(core, program, peripheral);

  // NOP
  sgpl::advance_core(core, program, peripheral);

  // execute RegulatorGet
  sgpl::advance_core(core, program, peripheral);

  // check to make sure value was decayed
  REQUIRE(core.registers == emp::array<float, 8>{99, -9999999, 0, 0, 0, 0, 0, 0});

}
