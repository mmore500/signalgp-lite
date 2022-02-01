#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/spec/StarterConfig.hpp"
#include "sgpl/spec/TransposeWindowDisplacementGenerator_Pareto.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test TransposeWindowDisplacementGenerator_Pareto") {

  sgpl::tlrand.Reseed(1);

  sgpl::StarterConfig cfg;
  sgpl::TransposeWindowDisplacementGenerator_Pareto gen(cfg);

  const auto res = gen(10, 42);
  REQUIRE( std::clamp(res, -10, 42) == res );

}
