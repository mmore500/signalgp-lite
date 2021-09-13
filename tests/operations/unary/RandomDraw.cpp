#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/operations/unary/RandomDraw.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

using spec_t = sgpl::Spec<sgpl::OpLibrary<sgpl::RandomDraw>>;


auto map_between_plusminus_one = [](const typename spec_t::tag_t& tag) {
  constexpr double max = 1.0;
  constexpr double min = -1.0;
  constexpr double max_double = spec_t::tag_t::MaxDouble();

  return  (tag.GetDouble() / max_double) * (max - min) + min;
};

auto is_odd = [](const typename spec_t::tag_t& tag) {
  return tag.Get(0);
};

auto map_up = [](const double plusminus_unit_val) {
  return 1.0 / (
    plusminus_unit_val * plusminus_unit_val * plusminus_unit_val
  );
};

auto map_draw = [](emp::Random& rand) -> double {
  const typename spec_t::tag_t tag( rand );
  return is_odd( tag )
    ? map_up( map_between_plusminus_one(tag) )
    : map_between_plusminus_one( tag )
  ;
};

TEST_CASE("Test RandomDraw") {
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
  REQUIRE(core.registers == emp::array<float, 8>{0, 0, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{static_cast<float>(map_draw(rand)), 0, 0, 0, 0, 0, 0, 0});

}
