#include <algorithm>
#include <cmath>
#include <numeric>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"
#include "Empirical/include/emp/math/constants.hpp"
#include "Empirical/include/emp/math/Random.hpp"

#include "sgpl/utility/do_random_walk_normal_approximation.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test do_random_walk_normal_approximation various lengths") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  for (int length : emp::vector<int>{ 2, 9, 10, 20, 100 } ) {

    emp::vector<int> walks;
    std::generate_n(
      std::back_inserter(walks), 100,
      [length](){ return sgpl::do_random_walk_normal_approximation(length); }
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
