#include <algorithm>
#include <cmath>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/utility/random_sign.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test random_sign p_positive=1.0") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  emp::vector<int> signs;
  std::generate_n(
    std::back_inserter(signs), 100,
    [](){ return sgpl::random_sign(1.0); }
  );

  REQUIRE( std::all_of(
    std::begin(signs), std::end(signs),
    [](const auto sign){ return sign == 1; }
  ) );

}

TEST_CASE("Test random_sign p_positive=0.0") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  emp::vector<int> signs;
  std::generate_n(
    std::back_inserter(signs), 100,
    [](){ return sgpl::random_sign(0.0); }
  );

  REQUIRE( std::all_of(
    std::begin(signs), std::end(signs),
    [](const auto sign){ return sign == -1; }
  ) );

}

TEST_CASE("Test random_sign p_positive=0.5") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  emp::vector<int> signs;
  std::generate_n(
    std::back_inserter(signs), 100,
    [](){ return sgpl::random_sign(0.5); }
  );

  REQUIRE( std::all_of(
    std::begin(signs), std::end(signs),
    [](const auto sign){ return std::abs(sign) == 1; }
  ) );
  REQUIRE( std::any_of(
    std::begin(signs), std::end(signs),
    [](const auto sign){ return sign == 1; }
  ) );
  REQUIRE( std::any_of(
    std::begin(signs), std::end(signs),
    [](const auto sign){ return sign == -1; }
  ) );

}
