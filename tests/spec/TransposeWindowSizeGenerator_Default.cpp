#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/spec/TransposeWindowSizeGenerator_Default.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test TransposeWindowSizeGenerator_Default") {

  sgpl::tlrand.Reseed(1);

  sgpl::TransposeWindowSizeGenerator_Default gen{};

  const auto res = gen(42);
  REQUIRE( std::clamp(res, 0, 42) == res );

}
