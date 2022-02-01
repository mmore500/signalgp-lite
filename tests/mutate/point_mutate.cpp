#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/mutate/point_mutate.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/spec/StarterConfig.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

using spec_t = sgpl::Spec<>;

TEST_CASE("Test point_mutate, mutation enabled") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  sgpl::Program<spec_t> original( 1000 );
  sgpl::Program<spec_t> copy( original );

  const size_t res = sgpl::point_mutate( copy, cfg );

  REQUIRE( res );
  REQUIRE( original != copy );

}

TEST_CASE("Test point_mutate, mutation disabled") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  cfg.Set("SGPL_POINTMUTATE_BITFLIP_RATE", "0.f");

  sgpl::Program<spec_t> original( 1000 );
  sgpl::Program<spec_t> copy( original );

  const size_t res = sgpl::point_mutate( copy, cfg );

  REQUIRE( res == 0 );
  REQUIRE( original == copy );

}
