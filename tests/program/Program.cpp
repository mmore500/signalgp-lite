#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "Empirical/source/tools/Random.h"

#include "sgpl/program/Program.hpp"

TEST_CASE("Test Program") {

  emp::Random rand;

  // TODO flesh out stub test
  sgpl::Program{
    rand,
    100
  };

}
