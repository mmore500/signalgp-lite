#include <algorithm>
#include <iterator>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/spec/InstRangeCopier_Perfect.hpp"
#include "sgpl/spec/StarterConfig.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test InstRangeCopier_Perfect") {

  sgpl::tlrand.Reseed(1);

  // setup test assets
  emp::vector<int> from(100);
  std::iota(std::begin(from), std::end(from), 1);

  emp::vector<int> to;

  // do the copy
  sgpl::StarterConfig cfg;
  sgpl::InstRangeCopier_Perfect copier{ cfg };
  copier(std::cbegin(from), std::cend(from), std::back_inserter(to));

  // everything in copy should be from original
  for (auto v : to) {
    REQUIRE( std::count(std::cbegin(from), std::cend(from), v) );
  }

}
