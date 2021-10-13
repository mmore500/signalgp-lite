#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/array.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/flow_local/RegulatorAdj.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<
  sgpl::local::Anchor,
  sgpl::local::RegulatorAdj,
  sgpl::local::RegulatorGet,
  sgpl::local::RegulatorSet
>;
struct spec_t : public sgpl::Spec<library_t>{
  // ensure that we step through operations one-by-one
  static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
  // lower number of registers, as 8 are not needed
  static constexpr inline size_t num_registers{ 4 }; // eslint-disable-line no-eval
};

TEST_CASE("Test RegulatorAdj") {
  const sgpl::Program<spec_t> program(std::filesystem::path{
    "assets/RegulatorAdj.json"
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

  // set register to a big number (amount to adjust by)
  core.registers[1] = 100000.f;

  REQUIRE(
    core.registers
    == emp::array<float, 4>{99.f, 100000.f, {}, {}}
  );

  // execute RegulatorAdj
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Adjust Local Regulator"
  );
  sgpl::advance_core(core, program);

  // NOP
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Local Anchor"
  );
  sgpl::advance_core(core, program);

  // execute RegulatorGet
  REQUIRE(
    program[core.GetProgramCounter()].GetOpName()
    == "Get Local Regulator"
  );
  sgpl::advance_core(core, program);

  // check to make sure value was adjusted
  REQUIRE(
    core.registers
    == emp::array<float, 4>{100099.f, 100000.f, {}, {}}
  );

}
