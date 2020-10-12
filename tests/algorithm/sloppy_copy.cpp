#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/source/base/vector.h"

#include "sgpl/algorithm/sloppy_copy.hpp"

TEST_CASE("Test sloppy_copy without mutation") {

  emp::vector<int> original( 100 );
  std::iota( std::begin( original ), std::end( original ), 0 );

  REQUIRE( original == sgpl::sloppy_copy( original, 1.0f, 0 ) );

}

TEST_CASE("Test sloppy_copy with mild mutation") {

  emp::vector<int> original( 100 );
  std::iota( std::begin( original ), std::end( original ), 0 );

  emp::vector<int> copy = sgpl::sloppy_copy( original, 0.1f, 2 );

  REQUIRE( copy != original );

  REQUIRE( std::all_of(
    std::begin( copy ),
    std::begin( copy ),
    [&original](const int val){
      return std::find(
        std::begin( original ),
        std::end( original ),
        val
      ) != std::end( original );
    }
  ) );

}


TEST_CASE("Test sloppy_copy with severe mutation") {

  emp::vector<int> original( 100 );
  std::iota( std::begin( original ), std::end( original ), 0 );

  emp::vector<int> copy = sgpl::sloppy_copy( original, 0.1f, original.size() );

  REQUIRE( copy != original );

  REQUIRE( std::all_of(
    std::begin( copy ),
    std::begin( copy ),
    [&original](const int val){
      return std::find(
        std::begin( original ),
        std::end( original ),
        val
      ) != std::end( original );
    }
  ) );

}
