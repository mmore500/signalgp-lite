#include <algorithm>
#include <numeric>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/algorithm/drag_to.hpp"

TEST_CASE("Test forward slide") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[1], &buff[3], &buff[5] )
    == &buff[3]
  );
  REQUIRE( buff == emp::vector<int>{0, 3, 4, 1, 2, 5, 6, 7} );

}

TEST_CASE("Test forward slide to end") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[1], &buff[4], &buff[7]+1 )
    == &buff[5]
  );
  REQUIRE( buff == emp::vector<int>{0, 4, 5, 6, 7, 1, 2, 3} );


  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[1], &buff[4], &buff[7] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 4, 5, 6, 1, 2, 3, 7} );

}

TEST_CASE("Test backward slide") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[5], &buff[7], &buff[1] )
    == &buff[1]
  );
  REQUIRE( buff == emp::vector<int>{0, 5, 6, 1, 2, 3, 4, 7} );

}

TEST_CASE("Test backward slide to front") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[5], &buff[7]+1, &buff[0] )
    == &buff[0]
  );
  REQUIRE( buff == emp::vector<int>{5, 6, 7, 0, 1, 2, 3, 4} );

}

TEST_CASE("Test internal slide") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[7], &buff[4] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[7], &buff[5] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[7], &buff[6] )
    == &buff[5]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 6, 4, 5, 7} );

  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[7], &buff[7] )
    == &buff[6]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 5, 6, 4, 7} );
}

TEST_CASE("Test bigger internal slide") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[7]+1, &buff[4] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[7]+1, &buff[5] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[7]+1, &buff[6] )
    == &buff[5]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 7, 4, 5, 6} );

  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[7]+1, &buff[7] )
    == &buff[6]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 6, 7, 4, 5} );

  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[7]+1, &buff[7]+1 )
    == &buff[7]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 5, 6, 7, 4} );
}

TEST_CASE("Test small internal slide") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[5], &buff[4] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[5], &buff[5] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[5], &buff[6] )
    == &buff[5]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 5, 4, 6, 7} );
}

TEST_CASE("Test no-op slides") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[7], &buff[4] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[4], &buff[4] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[7], &buff[5] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[4], &buff[5] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[4], &buff[7] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::drag_to( &buff[4], &buff[4], &buff[0] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

}
