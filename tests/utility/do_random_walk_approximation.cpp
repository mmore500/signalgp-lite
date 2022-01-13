#include <algorithm>
#include <cmath>
#include <numeric>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"
#include "Empirical/include/emp/math/constants.hpp"
#include "Empirical/include/emp/math/Random.hpp"

#include "sgpl/utility/do_random_walk_approximation.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test do_random_walk_approximation length 0") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  emp::vector<int> walks;
  std::generate_n(
    std::back_inserter(walks), 100,
    [](){ return sgpl::do_random_walk_approximation(0); }
  );
  REQUIRE( std::count( std::begin(walks), std::end(walks), 0 ) == 100 );

}

TEST_CASE("Test do_random_walk_approximation length 1") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  emp::vector<int> walks;
  std::generate_n(
    std::back_inserter(walks), 100,
    [](){ return sgpl::do_random_walk_approximation(1); }
  );
  REQUIRE( std::count(std::begin(walks), std::end(walks), 1 ) < 65 );
  REQUIRE( std::count(std::begin(walks), std::end(walks), 1 ) > 35 );

}

TEST_CASE("Test do_random_walk_approximation length 2") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  emp::vector<int> walks;
  std::generate_n(
    std::back_inserter(walks), 100,
    [](){ return sgpl::do_random_walk_approximation(2); }
  );
  REQUIRE( std::all_of(
    std::begin(walks), std::end(walks),
    [](const auto val){ return val == -2 || val == 0 || val == 2; }
  ) );
  REQUIRE(
    std::count(std::begin(walks), std::end(walks), 0 )
    > std::count(std::begin(walks), std::end(walks), 2 )
  );
  REQUIRE(
    std::count(std::begin(walks), std::end(walks), 0 )
    > std::count(std::begin(walks), std::end(walks), -2 )
  );
  REQUIRE(
    std::abs(
      std::count(std::begin(walks), std::end(walks), 2 )
      - std::count(std::begin(walks), std::end(walks), -2 )
    ) < 10
  );

}


TEST_CASE("Test do_random_walk_approximation various lengths") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  for (int length : emp::vector<int>{ 2, 9, 10, 20, 100 } ) {

    emp::vector<int> walks;
    std::generate_n(
      std::back_inserter(walks), 100,
      [length](){ return sgpl::do_random_walk_approximation(length); }
    );

    // mean displacement should approximate sqrt(n)
    // see https://www.mit.edu/~kardar/teaching/projects/chemotaxis(AndreaSchmidt)/random.htm
    // and https://math.stackexchange.com/a/103170
    const double actual_mean_disp = std::accumulate(
      std::begin(walks), std::end(walks),
      double{},
      [](const auto sum, const auto cur) { return sum + std::abs(cur); }
    ) / walks.size();
    const auto expected_mean_disp = std::sqrt(2*length/emp::PI);
    REQUIRE( actual_mean_disp == Approx(expected_mean_disp).margin(1) );

  }

}
