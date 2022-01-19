#include <algorithm>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/algorithm/prev.hpp"

TEST_CASE("Test bounded prev") {

  emp::vector<int> buff(3);

  const auto it = std::end(buff);
  const auto bound = std::begin(buff);

  REQUIRE( sgpl::prev(it, bound, 2) == std::prev(it, 2) );
  REQUIRE( sgpl::prev(it, bound, 3) == std::prev(it, 3) );
  REQUIRE( sgpl::prev(it, bound, 4) == std::begin(buff) );

}
