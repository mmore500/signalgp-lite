#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/spec/StarterConfig.hpp"
#include "sgpl/spec/TransposeWindowSizeGenerator_Pareto.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test TransposeWindowSizeGenerator_Pareto") {

  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  sgpl::TransposeWindowSizeGenerator_Pareto gen(cfg);

  const auto res = gen(42);
  REQUIRE( std::clamp(res, 0, 42) == res );

}
