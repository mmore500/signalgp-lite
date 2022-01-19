#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/spec/TransposeWindowDisplacementGenerator_Default.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test TransposeWindowDisplacementGenerator_Default") {

  sgpl::tlrand.Reseed(1);

  sgpl::TransposeWindowDisplacementGenerator_Default gen{};

  const auto res = gen(10, 42);
  REQUIRE( std::clamp(res, -10, 42) == res );

}
