#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/array.hpp"

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
  // ensure that we step through operations one-by-one
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 }; // eslint-disable-line no-eval
};

TEST_CASE("Test RegulatorSet") {
  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/RegulatorSet.json"
  });

  sgpl::Core<spec_t> core({99.f, {}, {}, {}});

  // load all anchors manually
  core.LoadLocalAnchors(program);

  // execute RegulatorSet
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Set Local Regulator"
  );
  sgpl::advance_core(core, program);

  // clear register
  core.registers[0] = 0.f;

  // check that registers were cleared
  REQUIRE(core.registers == emp::array<float, 4>{0.f, {}, {}, {}});

  // execute RegulatorGet
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Get Local Regulator"
  );
  sgpl::advance_core(core, program);

  // check to make sure value was retrieved
  REQUIRE(core.registers == emp::array<float, 4>{99.f, {}, {}, {}});

}
