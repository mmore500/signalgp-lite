#include "Catch/single_include/catch2/catch.hpp"

#include "../LoadProgram.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_local/RegulatorSet.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<
  sgpl::local::Anchor,
  sgpl::local::RegulatorGet,
  sgpl::local::RegulatorSet
>;
struct spec_t : public sgpl::Spec<library_t>{
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 };
};

TEST_CASE("Test RegulatorSet") {
  sgpl::Program<spec_t> program = sgpl::test::LoadProgram<spec_t>("RegulatorSet");

  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  core.registers[0] = 99;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 4>{99, 0, 0, 0});

  // execute RegulatorSet
  sgpl::advance_core(core, program);

  // clear register
  core.registers[0] = 0;

  // check that registers were cleared
  REQUIRE(core.registers == emp::array<float, 4>{0, 0, 0, 0});

  // execute RegulatorGet
  sgpl::advance_core(core, program);

  // check to make sure value was retrieved
  REQUIRE(core.registers == emp::array<float, 4>{99, 0, 0, 0});

}
