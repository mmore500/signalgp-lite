#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "cereal/include/cereal/archives/json.hpp"
#include "Empirical/source/tools/Random.h"

#include "sgpl/config/Spec.hpp"
#include "sgpl/program/Program.hpp"

using spec_t = sgpl::Spec<>;

TEST_CASE("Test Program") {

  emp::Random rand;

  // TODO flesh out stub test
  sgpl::Program<spec_t> program{
    rand,
    100
  };

  cereal::JSONOutputArchive archive( std::cout );

  archive( program );

}
