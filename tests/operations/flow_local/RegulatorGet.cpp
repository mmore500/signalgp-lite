#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/array.hpp"

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
  // ensure that we step through operations one-by-one
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 }; // eslint-disable-line no-eval
};

TEST_CASE("Test RegulatorGet") {
  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/RegulatorGet.json"
  });

  sgpl::Core<spec_t> core({1.0f, {}, {}, {}});

  // load all anchors manually
  core.LoadLocalAnchors(program);

  // execute single instruction
  sgpl::advance_core(core, program);

  // check final state (value is 0 by default)
  REQUIRE(core.registers == emp::array<float, 4>{0.f, {}, {}, {}});

}
