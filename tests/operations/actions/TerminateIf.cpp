#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/operations/actions/TerminateIf.hpp"


#include "sgpl/hardware/Core.hpp"
#include "sgpl/program/Program.hpp"

#include "sgpl/algorithm/execute_core.hpp"

#include "sgpl/spec/Spec.hpp"

#include "sgpl/utility/EmptyType.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::TerminateIf>;

using spec_t = sgpl::Spec<library_t>;

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test TerminateIf") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set register to true
  core.registers[0] = true;

  // tell terminateif to check inside the 0th register
  program[0].args[0] = 0;

  // check initial state
  REQUIRE(!core.HasTerminated());

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check final state
  REQUIRE(core.HasTerminated());
}
