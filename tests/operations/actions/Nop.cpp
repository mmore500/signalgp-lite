#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/operations/actions/Nop.hpp"

#include "sgpl/utility/ThreadLocalRandom.hpp"

#include "sgpl/hardware/Core.hpp"
#include "sgpl/program/Program.hpp"

#include "sgpl/algorithm/execute_core.hpp"

#include "sgpl/spec/Spec.hpp"

#include "sgpl/utility/EmptyType.hpp"

TEMPLATE_TEST_CASE_SIG("Test Nop", "[Nop]",
  ((int K), K), 1, 2, 3, 4, 5
) {
  // define spec
  using spec_t = sgpl::Spec<sgpl::OpLibrary<sgpl::Nop<K>>>;

  // create peripheral
  typename spec_t::peripheral_t peripheral;

  emp::Random rand(1);

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  // check that internal RNG is what we expect
  REQUIRE(sgpl::tlrand.Get().GetUInt() == rand.GetUInt());

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // advance our rand K times
  for (int i{}; i < K; ++i) rand.StepEngine();

  // check that internal RNG has been advanced as we expect
  REQUIRE(sgpl::tlrand.Get().GetUInt() == rand.GetUInt());
}
