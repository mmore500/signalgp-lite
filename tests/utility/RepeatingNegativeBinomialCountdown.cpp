#include <algorithm>
#include <cmath>
#include <numeric>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/utility/RepeatingNegativeBinomialCountdown.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test RepeatingNegativeBinomialCountdown p=1.0") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::RepeatingNegativeBinomialCountdown countdown(1.0);

  for (size_t i{}; i < 100; ++i) REQUIRE( countdown.TestAndStep() );

}

TEST_CASE("Test RepeatingNegativeBinomialCountdown p=0.0000001") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::RepeatingNegativeBinomialCountdown countdown(0.0000001);

  for (size_t i{}; i < 100; ++i) REQUIRE( !countdown.TestAndStep() );

}

TEST_CASE("Test RepeatingNegativeBinomialCountdown p=0.5") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  sgpl::RepeatingNegativeBinomialCountdown countdown(0.5);

  emp::vector<bool> tests;
  std::generate_n(
    std::back_inserter(tests), 100,
    [&countdown](){ return countdown.TestAndStep(); }
  );

  // about equal success and failure
  const double frac_true = std::accumulate(
    std::begin(tests), std::end(tests), double{}
  ) / tests.size();
  REQUIRE( std::clamp( frac_true, 0.4, 0.6 ) == frac_true );

  // check not just alternating
  REQUIRE(
    std::adjacent_find( std::begin(tests), std::end(tests) )
    != std::end(tests)
  );

}
