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
