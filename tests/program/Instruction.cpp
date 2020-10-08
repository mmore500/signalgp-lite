#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "Empirical/source/tools/Random.h"

#include "sgpl/config/Spec.hpp"
#include "sgpl/program/Instruction.hpp"

using spec_t = sgpl::Spec<>;

TEST_CASE("Test Instruction") {

  emp::Random rand;

  // TODO flesh out stub test
  sgpl::Instruction<spec_t>{};

  sgpl::Instruction<spec_t>{ rand };

}
