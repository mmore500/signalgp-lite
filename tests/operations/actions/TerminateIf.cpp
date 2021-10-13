#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/filesystem.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/actions/TerminateIf.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<
  sgpl::Nop<>,
  sgpl::TerminateIf
>;
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 2 }; // eslint-disable-line no-eval
};

TEST_CASE("Test TerminateIf, true test flag") {

  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/TrueTerminateIf.json"
  });

  sgpl::Core<spec_t> core( {true, {}} );

  // check initial state
  REQUIRE(!core.HasTerminated());

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state
  REQUIRE(core.HasTerminated());
}


TEST_CASE("Test TerminateIf, false test flag") {

  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/FalseTerminateIf.json"
  });

  sgpl::Core<spec_t> core;

  // check initial state
  REQUIRE(!core.HasTerminated());

  // execute single instruction
  sgpl::advance_core(core, program);

  // check that it did not terminate
  REQUIRE(!core.HasTerminated());
}
