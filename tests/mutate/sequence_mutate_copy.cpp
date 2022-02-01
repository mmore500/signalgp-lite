#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/mutate/sequence_mutate_copy.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/spec/StarterConfig.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

using spec_t = sgpl::Spec<>;

TEST_CASE("Test sequence_mutate_copy, mutation enabled") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  cfg.Set("SGPL_SEQMUTATE_INST_INDEL_RATE", "0.1f");
  cfg.Set("SGPL_SEQMUTATE_MODULE_INDEL_RATE", "0.1f");

  const sgpl::Program<spec_t> original( 1000 );

  const auto [copy, n_muts] = sgpl::sequence_mutate_copy( original, cfg );

  REQUIRE( n_muts );
  REQUIRE( original != copy );

}

TEST_CASE("Test sequence_mutate_copy, just inst mutation enabled") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  cfg.Set("SGPL_SEQMUTATE_INST_INDEL_RATE", "0.1f");
  cfg.Set("SGPL_SEQMUTATE_MODULE_INDEL_RATE", "0.f");

  const sgpl::Program<spec_t> original( 1000 );

  const auto [copy, n_muts] = sgpl::sequence_mutate_copy( original, cfg );

  REQUIRE( n_muts );
  REQUIRE( original != copy );

}

TEST_CASE("Test sequence_mutate_copy, just module mutation enabled") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  cfg.Set("SGPL_SEQMUTATE_INST_INDEL_RATE", "0.f");
  cfg.Set("SGPL_SEQMUTATE_MODULE_INDEL_RATE", "0.1f");

  const sgpl::Program<spec_t> original( 1000 );

  const auto [copy, n_muts] = sgpl::sequence_mutate_copy( original, cfg );

  REQUIRE( n_muts );
  REQUIRE( original != copy );

}

TEST_CASE("Test sequence_mutate_copy, mutation disabled") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  cfg.Set("SGPL_SEQMUTATE_INST_INDEL_RATE", "0.f");
  cfg.Set("SGPL_SEQMUTATE_MODULE_INDEL_RATE", "0.f");

  const sgpl::Program<spec_t> original( 1000 );

  const auto [copy, n_muts] = sgpl::sequence_mutate_copy( original, cfg );

  REQUIRE( n_muts == 0 );
  REQUIRE( original == copy );

}

TEST_CASE("Test sequence_mutate_copy, hitting program size cap") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  cfg.Set("SGPL_SEQMUTATE_INST_INDEL_RATE", "0.5f");
  cfg.Set("SGPL_SEQMUTATE_INST_INDEL_FRAC_INSERTIONS", "1.f");
  cfg.Set("SGPL_SEQMUTATE_MODULE_INDEL_RATE", "0.5f");
  cfg.Set("SGPL_SEQMUTATE_MODULE_INDEL_FRAC_INSERTIONS", "1.f");
  cfg.Set("SGPL_PROGRAM_SIZE_CAP", "1000");

  const sgpl::Program<spec_t> original( cfg.SGPL_PROGRAM_SIZE_CAP() );

  const auto [copy, n_muts] = sgpl::sequence_mutate_copy( original, cfg );

  REQUIRE( n_muts );
  REQUIRE( original != copy );
  REQUIRE( original.size() == cfg.SGPL_PROGRAM_SIZE_CAP() );

}
