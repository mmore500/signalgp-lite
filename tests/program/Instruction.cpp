#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "Empirical/source/tools/Random.h"

#include "sgpl/program/Instruction.hpp"

TEST_CASE("Test Instruction") {

  emp::Random rand;

  // TODO flesh out stub test
  sgpl::Instruction{};

  sgpl::Instruction{ rand };

}
