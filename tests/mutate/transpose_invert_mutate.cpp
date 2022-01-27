#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/mutate/transpose_invert_mutate.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/spec/StarterConfig.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

using spec_t = sgpl::Spec<>;

TEST_CASE("Test transpose_invert_mutate, mutation enabled") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  cfg.Set("SGPL_SEQMUTATE_INST_TRANSPOSE_RATE", "0.5f");

  sgpl::Program<spec_t> original( 1000 );

  sgpl::Program<spec_t> mutated( original );
  REQUIRE( original == mutated );
  const size_t res = sgpl::transpose_invert_mutate( mutated, cfg );

  REQUIRE( res );
  REQUIRE( original != mutated );

  std::sort(std::begin(original), std::end(original));
  std::sort(std::begin(mutated), std::end(mutated));
  REQUIRE( original == mutated );

}

TEST_CASE("Test transpose_invert_mutate, mutation disabled") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  cfg.Set("SGPL_SEQMUTATE_INST_TRANSPOSE_RATE", "0.f");

  sgpl::Program<spec_t> original( 10000 );
  sgpl::Program<spec_t> copy( original );

  const size_t res = sgpl::transpose_invert_mutate( copy, cfg );

  REQUIRE( res == 0 );
  REQUIRE( original == copy );

}
