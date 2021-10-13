#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/math/Random.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/actions/Nop.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

// typedefs
template<size_t K> using library_t = sgpl::OpLibrary<sgpl::Nop<K>>;
template<size_t K> using spec_t = sgpl::Spec<library_t<K>>;
template<size_t K> using core_t = sgpl::Core<spec_t<K>>;
template<size_t K> using program_t = sgpl::Program<spec_t<K>>;

/**
 * This is a templated test case.
 * This means that a unique test case will be created
 * for each of the size_t's in the title, with K substituted in.
 * K represents the number of RNG touches applied by the Nop instruction.
*/
TEMPLATE_TEST_CASE_SIG("Test Nop", "[Nop]",
  ((size_t K), K), 1, 2, 3, 4, 5
) {

  const program_t<K> program(1);

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
  for (size_t touch{}; touch < K; ++touch) comparison_rand.StepEngine();

  // check that internal RNG has been advanced as we expect
  REQUIRE(sgpl::tlrand.Get().GetUInt() == comparison_rand.GetUInt());

  // check that cores are equivalent
  REQUIRE(core == core_copy);
}
