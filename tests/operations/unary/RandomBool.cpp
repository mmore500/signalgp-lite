#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/operations/unary/RandomBool.hpp"

#include "sgpl/utility/ThreadLocalRandom.hpp"

#include "sgpl/hardware/Core.hpp"
#include "sgpl/program/Program.hpp"

#include "sgpl/algorithm/execute_core.hpp"

#include "sgpl/spec/Spec.hpp"

#include "sgpl/utility/EmptyType.hpp"

using spec_t = sgpl::Spec<sgpl::OpLibrary<sgpl::RandomBool>>;

auto map_to_unit = [](const typename spec_t::tag_t& tag) -> double {

  constexpr double max_double = spec_t::tag_t::MaxDouble();

  return tag.GetDouble() / max_double;

};

TEMPLATE_TEST_CASE_SIG("Test RandomBool", "[Nop]",
  ((int K), K), 1, 2, 3, 4, 5
) {
  // create peripheral
  typename spec_t::peripheral_t peripheral;

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up what register to operate on
  program[0].args[0] = 0;

  // initialize rand
  emp::Random rand(1);

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  // check that internal RNG is what we expect
  REQUIRE(sgpl::tlrand.Get().GetUInt() == rand.GetUInt());

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{99, 0, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // get p
  const double p = map_to_unit(program[0].tag);

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{static_cast<float>(rand.P(p)), 0, 0, 0, 0, 0, 0, 0});
}
