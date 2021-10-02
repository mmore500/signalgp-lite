#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/actions/Nop.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

/**
 * This is a templated test case.
 * This means that a unique test case will be created
 * for each of the ints in the title, with K substituted in.
*/
TEMPLATE_TEST_CASE_SIG("Test Nop", "[Nop]",
  ((int K), K), 1, 2, 3, 4, 5
) {
  // define spec
  using spec_t = sgpl::Spec<sgpl::OpLibrary<sgpl::Nop<K>>>;

  // create peripheral
  typename spec_t::peripheral_t peripheral;

  sgpl::Program<spec_t> program(1);

  sgpl::Core<spec_t> core;

  // initialize tlrand and comparison rand with the same seed
  sgpl::tlrand.Reseed(1);
  emp::Random comparison_rand(1);

  // check that internal RNG is what we expect
  REQUIRE(sgpl::tlrand.Get().GetUInt() == comparison_rand.GetUInt());

  // create copy of core
  sgpl::Core<spec_t> core_copy = core;

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // advance our rand K times
  for (int i{}; i < K; ++i) comparison_rand.StepEngine();

  // check that internal RNG has been advanced as we expect
  REQUIRE(sgpl::tlrand.Get().GetUInt() == comparison_rand.GetUInt());

  // check that cores are equivalent
  REQUIRE(core_copy == core);
}
