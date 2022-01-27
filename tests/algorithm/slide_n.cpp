#include <algorithm>
#include <numeric>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/algorithm/slide_n.hpp"

TEST_CASE("Test forward slide") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_n( &buff[1], &buff[3], 2 )
    == &buff[3]
  );
  REQUIRE( buff == emp::vector<int>{0, 3, 4, 1, 2, 5, 6, 7} );

}

TEST_CASE("Test forward slide to end") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_n( &buff[1], &buff[4], 4 )
    == &buff[5]
  );
  REQUIRE( buff == emp::vector<int>{0, 4, 5, 6, 7, 1, 2, 3} );

  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_n( &buff[1], &buff[4], 3 )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 4, 5, 6, 1, 2, 3, 7} );

}

TEST_CASE("Test backward slide") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_n( &buff[5], &buff[7], -4 )
    == &buff[1]
  );
  REQUIRE( buff == emp::vector<int>{0, 5, 6, 1, 2, 3, 4, 7} );

}

TEST_CASE("Test backward slide to front") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_n( &buff[5], &buff[7]+1, -5 )
    == &buff[0]
  );
  REQUIRE( buff == emp::vector<int>{5, 6, 7, 0, 1, 2, 3, 4} );

}

TEST_CASE("Test no-op slides") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_n( &buff[4], &buff[7], 0 )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_n( &buff[4], &buff[4], 0 )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  // empty window
  REQUIRE(
    sgpl::slide_n( &buff[4], &buff[4], 2 )
    == &buff[6]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  // empty window
  REQUIRE(
    sgpl::slide_n( &buff[4], &buff[4], -1 )
    == &buff[3]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

}
