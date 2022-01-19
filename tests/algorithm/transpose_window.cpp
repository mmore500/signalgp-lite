#include <algorithm>
#include <numeric>
#include <ratio>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/algorithm/transpose_window.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test transpose_window") {

  sgpl::tlrand.Reseed(1);

  size_t num_op_transposes{};
  size_t num_nop_transposes{};
  for (size_t rep{}; rep < std::kilo::num; ++rep) {

    emp::vector<int> buff(rep);
    std::iota( std::begin(buff), std::end(buff), 0 );

    const auto before_copy = buff;

    const auto [
      window_before_first,
      window_after_first,
      window_after_last
    ] = sgpl::transpose_window(
      std::begin(buff), std::end(buff)
    );

    REQUIRE( std::is_sorted(std::begin(buff), window_after_first) );
    REQUIRE( std::is_sorted(window_after_first, window_after_last) );
    REQUIRE( std::is_sorted(window_after_last, std::end(buff)) );

    if (
      window_before_first != window_after_first
      && window_after_first != window_after_last
    ) {
      REQUIRE( before_copy != buff );
      ++num_op_transposes;
    } else {
      REQUIRE( before_copy == buff );
      ++num_nop_transposes;
    }

  }

  REQUIRE( num_nop_transposes );
  REQUIRE( num_op_transposes );
  REQUIRE( num_op_transposes > num_nop_transposes );

}
