#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_local/RegulatorGet.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<
  sgpl::local::Anchor,
  sgpl::local::RegulatorGet
>;
struct spec_t : public sgpl::Spec<library_t>{
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 };
};

TEST_CASE("Test RegulatorGet") {
  sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/RegulatorGet.json"
  });

  sgpl::Core<spec_t> core;

  // load all anchors manually
  core.LoadLocalAnchors(program);

  core.registers[0] = 1;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 4>{1, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state (value is 0 by default)
  REQUIRE(core.registers == emp::array<float, 4>{0, 0, 0, 0});

}
