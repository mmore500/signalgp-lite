#include <vector>

#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/utility/CappedOutputIterator.hpp"

TEST_CASE("Test CappedOutputIterator below capacity") {

  std::vector<int> vec;
  auto it = sgpl::CappedOutputIterator(std::back_inserter(vec), 9);

  std::generate_n( it, 3, [](){ return int{}; } );

  REQUIRE( vec.size() == 3 );

}

TEST_CASE("Test CappedOutputIterator to capacity") {

  std::vector<int> vec;
  auto it = sgpl::CappedOutputIterator(std::back_inserter(vec), 9);

  std::generate_n( it, 9, [](){ return int{}; } );

  REQUIRE( vec.size() == 9 );

}

TEST_CASE("Test CappedOutputIterator above capacity") {

  std::vector<int> vec;
  auto it = sgpl::CappedOutputIterator(std::back_inserter(vec), 9);

  std::generate_n( it, 42, [](){ return int{}; } );

  REQUIRE( vec.size() == 9 );

}

TEST_CASE("Test copying CappedOutputIterator") {

  std::vector<int> vec;
  auto it = sgpl::CappedOutputIterator(std::back_inserter(vec), 9);
  auto it_copy = it;

  std::generate_n( it, 42, [](){ return int{}; } );
  std::generate_n( it_copy, 42, [](){ return int{}; } );

  REQUIRE( vec.size() == 9 );

}

TEST_CASE("Test moving CappedOutputIterator") {

  std::vector<int> vec;

  auto it = sgpl::CappedOutputIterator(std::back_inserter(vec), 9);

  std::generate_n( it, 42, [](){ return int{}; } );

  auto it_move = sgpl::CappedOutputIterator(std::move(it));

  std::generate_n( it_move, 42, [](){ return int{}; } );

  REQUIRE( vec.size() == 9 );

}
