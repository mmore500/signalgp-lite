#include <algorithm>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/algorithm/next.hpp"

TEST_CASE("Test bounded next") {

  emp::vector<int> buff(3);

  const auto it = std::begin(buff);
  const auto bound = std::end(buff);

  REQUIRE( sgpl::next(it, bound, 2) == std::next(it, 2) );
  REQUIRE( sgpl::next(it, bound, 3) == std::next(it, 3) );
  REQUIRE( sgpl::next(it, bound, 4) == std::end(buff) );

}
