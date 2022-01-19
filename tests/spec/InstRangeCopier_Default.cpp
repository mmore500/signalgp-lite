#include <algorithm>
#include <iterator>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/spec/InstRangeCopier_Default.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test InstRangeCopier_Default") {

  sgpl::tlrand.Reseed(1);

  // setup test assets
  emp::vector<int> from(100);
  std::iota(std::begin(from), std::end(from), 1);

  emp::vector<int> to;

  // do the copy
  sgpl::InstRangeCopier_Default copier{};
  copier(std::cbegin(from), std::cend(from), std::back_inserter(to));

  // everything in copy should be from original
  for (auto v : to) {
    REQUIRE( std::count(std::cbegin(from), std::cend(from), v) );
  }

}
