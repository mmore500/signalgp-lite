#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/actions/Nop.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

// typedefs
template<int K> using library_t = sgpl::OpLibrary<sgpl::Nop<K>>;
template<int K> using spec_t = sgpl::Spec<library_t<K>>;
template<int K> using core_t = sgpl::Core<spec_t<K>>;
template<int K> using program_t = sgpl::Program<spec_t<K>>;

/**
 * This is a templated test case.
 * This means that a unique test case will be created
 * for each of the ints in the title, with K substituted in.
 * K represents the number of RNG touches applied by the Nop instruction.
*/
TEMPLATE_TEST_CASE_SIG("Test Nop", "[Nop]",
  ((int K), K), 1, 2, 3, 4, 5
) {

  program_t<K> program(1);

  core_t<K> core;

  // initialize tlrand and comparison rand with the same seed
  sgpl::tlrand.Reseed(1);
  emp::Random comparison_rand(1);

  // check that internal RNG is what we expect
  REQUIRE(sgpl::tlrand.Get().GetUInt() == comparison_rand.GetUInt());

  // create copy of core
  core_t<K> core_copy = core;

  // execute single instruction
  sgpl::advance_core(core, program);

  // advance our rand K times
  for (int i{}; i < K; ++i) comparison_rand.StepEngine();

  // check that internal RNG has been advanced as we expect
  REQUIRE(sgpl::tlrand.Get().GetUInt() == comparison_rand.GetUInt());

  // check that cores are equivalent
  REQUIRE(core == core_copy);
}
