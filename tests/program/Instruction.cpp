#include "Catch/single_include/catch2/catch.hpp"

#include "Empirical/include/emp/math/Random.hpp"

#include "sgpl/program/Instruction.hpp"
#include "sgpl/spec/Spec.hpp"

using spec_t = sgpl::Spec<>;

TEST_CASE("Test Instruction default constructor") {

  // TODO flesh out stub test
  sgpl::Instruction<spec_t>{};

}

TEST_CASE("Test Instruction emp::Random constructor") {

  emp::Random rand(1);

  REQUIRE( sgpl::Instruction<spec_t>(rand) != sgpl::Instruction<spec_t>(rand) );

}
