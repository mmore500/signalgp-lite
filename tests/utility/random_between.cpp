#include <algorithm>
#include <cmath>

#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/debug/audit_cast.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/utility/random_between.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test random_between nonempty window") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  using container_t = emp::vector<int>;
  container_t container(10);
  emp::vector<container_t::iterator> selections;
  std::generate_n(
    std::back_inserter(selections), 100,
    [&](){ return sgpl::random_between(
      std::begin( container ), std::end( container )
    ); }
  );

  // test bounds
  REQUIRE( std::all_of(
    std::begin(selections), std::end(selections),
    [&](const auto select){
      return std::clamp(
        select,
        std::begin( container ), std::end( container )
      ) == select;
    }
  ) );

  // test distribution
  for (auto it = std::begin(container); it != std::end(container); ++it) {
    const int outcome_count = std::count(
      std::begin(selections), std::end(selections),
      it
    );
    REQUIRE( std::clamp(outcome_count, 5, 20) == outcome_count );
  }

}

TEST_CASE("Test random_between singleton window") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  using container_t = emp::vector<int>;
  container_t container(1);
  emp::vector<container_t::iterator> selections;
  std::generate_n(
    std::back_inserter(selections), 100,
    [&](){ return sgpl::random_between(
      std::begin( container ), std::end( container )
    ); }
  );

  REQUIRE( std::count(
    std::begin(selections), std::end(selections),
    std::begin(container)
  ) == uitsl::audit_cast<int>(selections.size()) );

}

TEST_CASE("Test random_between empty window") {

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  using container_t = emp::vector<int>;
  container_t container;
  emp::vector<container_t::iterator> selections;
  std::generate_n(
    std::back_inserter(selections), 100,
    [&](){ return sgpl::random_between(
      std::begin( container ), std::end( container )
    ); }
  );

  REQUIRE( std::count(
    std::begin(selections), std::end(selections),
    std::begin(container)
  ) == uitsl::audit_cast<int>(selections.size()) );

}
