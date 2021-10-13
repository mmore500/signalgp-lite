#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_local/JumpIfNot.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<
  sgpl::Nop<1>,
  sgpl::local::Anchor,
  sgpl::local::JumpIfNot
>;
struct spec_t : public sgpl::Spec<library_t>{
  // ensure that we step through operations one-by-one
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 2 }; // eslint-disable-line no-eval
};

TEST_CASE("Test JumpIfNot, false test flag") {
  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/JumpIfNot.json"
  });

  sgpl::Core<spec_t> core({ false, {}});

  // load all anchors manually
  core.LoadLocalAnchors(program);

  // set up values to operate on in register
  core.registers[0] = false;

  // check initial state
  REQUIRE(core.GetProgramCounter() == 0);

  // execute single instruction
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Local Jump If Not"
  );
  sgpl::advance_core(core, program);

  // make sure we jumped
  REQUIRE(core.GetProgramCounter() != 1);
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Local Anchor"
  );

}


TEST_CASE("Test JumpIfNot, true test flag") {
  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/JumpIfNot.json"
  });

  sgpl::Core<spec_t> core({true, {}});

  // load all anchors manually
  core.LoadLocalAnchors(program);

  // check initial state
  REQUIRE(core.GetProgramCounter() == 0);

  // execute single instruction
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Local Jump If Not"
  );
  sgpl::advance_core(core, program);

  // make sure we did not jump
  REQUIRE(core.GetProgramCounter() == 1);
}
