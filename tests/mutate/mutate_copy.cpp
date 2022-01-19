#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/mutate/mutate_copy.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/spec/StarterConfig.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

using spec_t = sgpl::Spec<>;

TEST_CASE("Test mutate_copy with mutations enabled") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;

  const sgpl::Program<spec_t> original( 1000 );

  const auto [copy, n_muts] = sgpl::mutate_copy( original, cfg );

  REQUIRE( n_muts );
  REQUIRE( original != copy );

}

TEST_CASE("Test mutate_copy with mutations disabled") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  cfg.Set("SGPL_POINTMUTATE_BITFLIP_RATE", "0.f");
  cfg.Set("SGPL_SEQMUTATE_INST_INDEL_RATE", "0.f");
  cfg.Set("SGPL_SEQMUTATE_MODULE_INDEL_RATE", "0.f");
  cfg.Set("SGPL_SEQMUTATE_INST_TRANSPOSE_RATE", "0.f");

  const sgpl::Program<spec_t> original( 1000 );

  const auto [copy, n_muts] = sgpl::mutate_copy( original, cfg );

  REQUIRE( n_muts == 0);
  REQUIRE( original == copy );

}
