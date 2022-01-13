#include <algorithm>
#include <vector>

#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/math/Random.hpp"

#include "sgpl/utility/GarbledOutputIterator.hpp"

struct GarbleTester {

  bool state{};

  GarbleTester() = default;

  GarbleTester( emp::Random& ) : state( true ) { ; }

};

TEST_CASE("Test GarbledOutputIterator without garble") {

  std::vector<GarbleTester> vec;
  auto it = sgpl::GarbledOutputIterator(std::back_inserter(vec));

  std::generate_n( it, 3, [](){ return GarbleTester{}; } );

  REQUIRE( vec.size() == 3 );
  REQUIRE( std::none_of(
    std::begin(vec), std::end(vec),
    [](const auto& v){ return v.state; }
  ) );

}

TEST_CASE("Test GarbledOutputIterator with random garble") {

  std::vector<GarbleTester> vec;
  auto it = sgpl::GarbledOutputIterator(std::back_inserter(vec));
  it.AddGarble( 2 );

  ++*it = {};
  REQUIRE( vec.back().state );

  ++*it = {};
  REQUIRE( vec.back().state );

  ++*it = {};
  REQUIRE( !vec.back().state );

  it.AddGarble( 1 );

  ++*it = {};
  REQUIRE( vec.back().state );

  ++*it = {};
  REQUIRE( !vec.back().state );

}

struct GarbleTester2 {

  bool state{true};

  GarbleTester2() = default;

  GarbleTester2( int ) : state( false ) { ; }

};

TEST_CASE("Test GarbledOutputIterator with default garble") {

  std::vector<GarbleTester2> vec;
  auto it = sgpl::GarbledOutputIterator(std::back_inserter(vec));
  it.AddGarble( 2 );

  ++*it = {1};
  REQUIRE( vec.back().state );

  ++*it = {1};
  REQUIRE( vec.back().state );

  ++*it = {1};
  REQUIRE( !vec.back().state );

  it.AddGarble( 1 );

  ++*it = {1};
  REQUIRE( vec.back().state );

  ++*it = {1};
  REQUIRE( !vec.back().state );

}
