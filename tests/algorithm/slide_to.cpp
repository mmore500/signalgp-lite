#include <algorithm>
#include <numeric>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/algorithm/slide_to.hpp"

TEST_CASE("Test forward slide_to") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[1], &buff[3], &buff[5] )
    == &buff[3]
  );
  REQUIRE( buff == emp::vector<int>{0, 3, 4, 1, 2, 5, 6, 7} );

}

TEST_CASE("Test forward slide_to to end") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[1], &buff[4], &buff[7]+1 )
    == &buff[5]
  );
  REQUIRE( buff == emp::vector<int>{0, 4, 5, 6, 7, 1, 2, 3} );


  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[1], &buff[4], &buff[7] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 4, 5, 6, 1, 2, 3, 7} );

}

TEST_CASE("Test backward slide_to") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[5], &buff[7], &buff[1] )
    == &buff[1]
  );
  REQUIRE( buff == emp::vector<int>{0, 5, 6, 1, 2, 3, 4, 7} );

}

TEST_CASE("Test backward slide_to to front") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[5], &buff[7]+1, &buff[0] )
    == &buff[0]
  );
  REQUIRE( buff == emp::vector<int>{5, 6, 7, 0, 1, 2, 3, 4} );

}

TEST_CASE("Test internal slide_to") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[7], &buff[4] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[7], &buff[5] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[7], &buff[6] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[7], &buff[7] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );
}

TEST_CASE("Test bigger internal slide_to") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[7]+1, &buff[4] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[7]+1, &buff[5] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[7]+1, &buff[6] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[7]+1, &buff[7] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[7]+1, &buff[7]+1 )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );
}

TEST_CASE("Test small internal slide_to") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[5], &buff[4] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[5], &buff[5] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

}

TEST_CASE("Test no-op slide_to's") {

  emp::vector<int> buff(8);
  std::iota( std::begin(buff), std::end(buff), 0 );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[7], &buff[4] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[4], &buff[4] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[7], &buff[5] )
    == &buff[4]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[4], &buff[5] )
    == &buff[5]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[4], &buff[7] )
    == &buff[7]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

  REQUIRE(
    sgpl::slide_to( &buff[4], &buff[4], &buff[0] )
    == &buff[0]
  );
  REQUIRE( buff == emp::vector<int>{0, 1, 2, 3, 4, 5, 6, 7} );

}
