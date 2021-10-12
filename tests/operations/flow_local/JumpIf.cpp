#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_local/JumpIf.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<
  sgpl::Nop<1>,
  sgpl::local::Anchor,
  sgpl::local::JumpIf
>;
using spec_t = sgpl::Spec<library_t>;

TEST_CASE("Test JumpIf, true value") {
  sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/JumpIf.json"
  });

  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  // set up values to operate on in register
  core.registers[0] = true;

  // check initial state
  REQUIRE(core.GetProgramCounter() == 0);

  // execute single instruction
  sgpl::advance_core(core, program);

  // make sure we jumped
  REQUIRE(core.GetProgramCounter() != 1);
}


TEST_CASE("Test JumpIf, false value") {
  sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/JumpIf.json"
  });

  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  // set up values to operate on in register
  core.registers[0] = false;

  // check initial state
  REQUIRE(core.GetProgramCounter() == 0);

  // execute single instruction
  sgpl::advance_core(core, program);

  // make sure we did not jump
  REQUIRE(core.GetProgramCounter() == 1);
}
