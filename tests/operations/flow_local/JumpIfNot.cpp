#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_local/JumpIfNot.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<
  sgpl::Nop<>,
  sgpl::local::Anchor,
  sgpl::local::JumpIfNot
>;
using spec_t = sgpl::Spec<library_t>;

TEST_CASE("Test JumpIfNot, false value") {
  sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/JumpIfNot.json"
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

  // make sure we jumped
  REQUIRE(core.GetProgramCounter() != 1);
}


TEST_CASE("Test JumpIfNot, true value") {
  sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/JumpIfNot.json"
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

  // make sure we did not jump
  REQUIRE(core.GetProgramCounter() == 1);
}
