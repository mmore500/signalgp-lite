#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/algorithm/inst_indel_copy.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

TEST_CASE("Test inst_indel_copy without mutation") {

  sgpl::tlrand.Get() = emp::Random(1);

  emp::vector<int> original( 100 );
  std::iota( std::begin( original ), std::end( original ), 0 );

  emp::vector<int> copy;
  const auto num_muts = sgpl::inst_indel_copy(
    std::begin(original), std::end(original),
    std::back_inserter(copy),
    0.f
  );

  REQUIRE( original == copy );
  REQUIRE( num_muts == 0 );

}

TEST_CASE("Test inst_indel_copy without mutation with garbling") {

  sgpl::tlrand.Get() = emp::Random(1);

  emp::vector<int> original( 100 );
  std::iota( std::begin( original ), std::end( original ), 0 );

  emp::vector<int> copy;
  const auto num_muts = sgpl::inst_indel_copy(
    std::begin(original), std::end(original),
    std::back_inserter(copy),
    0.f, 1.f
  );

  REQUIRE( original == copy );
  REQUIRE( num_muts == 0 );

}

TEST_CASE("Test inst_indel_copy with mild mutation") {

  sgpl::tlrand.Get() = emp::Random(1);

  emp::vector<int> original( 100 );
  std::iota( std::begin( original ), std::end( original ), 1 );

  emp::vector<int> copy;
  const auto num_muts = sgpl::inst_indel_copy(
    std::begin(original), std::end(original),
    std::back_inserter(copy),
    0.1f
  );

  REQUIRE( copy != original );
  REQUIRE( num_muts > 0 );

  // do all of the items in copy come from somewhere in the original?
  REQUIRE( std::all_of(
    std::begin( copy ), std::end( copy ),
    [&original](const int val){
      return std::find(
        std::begin( original ), std::end( original ),
        val
      ) != std::end( original );
    }
  ) );

}

TEST_CASE("Test inst_indel_copy with severe mutation") {

  sgpl::tlrand.Get() = emp::Random(1);

  emp::vector<int> original( 100 );
  std::iota( std::begin( original ), std::end( original ), 1 );

  emp::vector<int> copy;
  const auto num_muts = sgpl::inst_indel_copy(
    std::begin(original), std::end(original),
    std::back_inserter(copy),
    1.f
  );

  REQUIRE( copy != original );
  REQUIRE( num_muts > 0 );

  // do all of the items in copy come from somewhere in the original?
  REQUIRE( std::all_of(
    std::begin( copy ), std::end( copy ),
    [&original](const int val){
      return std::find(
        std::begin( original ), std::end( original ),
        val
      ) != std::end( original );
    }
  ) );

}

TEST_CASE("Test inst_indel_copy with only insertion mutation") {

  sgpl::tlrand.Get() = emp::Random(1);

  emp::vector<int> original( 100 );
  std::iota( std::begin( original ), std::end( original ), 1 );

  emp::vector<int> copy;
  const auto num_muts = sgpl::inst_indel_copy(
    std::begin(original), std::end(original),
    std::back_inserter(copy),
    0.1f, 0.f, 1.f
  );

  REQUIRE( copy != original );
  REQUIRE( copy.size() > original.size() );
  REQUIRE( num_muts > 0 );

  // do all of the items in copy come from somewhere in the original?
  REQUIRE( std::all_of(
    std::begin( copy ), std::end( copy ),
    [&original](const int val){
      return std::find(
        std::begin( original ), std::end( original ),
        val
      ) != std::end( original );
    }
  ) );

}

TEST_CASE("Test inst_indel_copy with only deletion mutation") {

  sgpl::tlrand.Get() = emp::Random(1);

  emp::vector<int> original( 100 );
  std::iota( std::begin( original ), std::end( original ), 1 );

  emp::vector<int> copy;
  const auto num_muts = sgpl::inst_indel_copy(
    std::begin(original), std::end(original),
    std::back_inserter(copy),
    0.1f, 0.f, 0.f
  );

  REQUIRE( copy != original );
  REQUIRE( copy.size() < original.size() );
  REQUIRE( num_muts > 0 );

  // sorted order should be preserved
  REQUIRE( std::is_sorted( std::begin(copy), std::end(copy) ) );

  // do all of the items in copy come from somewhere in the original?
  REQUIRE( std::all_of(
    std::begin( copy ), std::end( copy ),
    [&original](const int val){
      return std::find(
        std::begin( original ), std::end( original ),
        val
      ) != std::end( original );
    }
  ) );

}

TEST_CASE("Test inst_indel_copy with garbling") {

  sgpl::tlrand.Get() = emp::Random(1);

  emp::vector<int> original( 100 );
  std::iota( std::begin( original ), std::end( original ), 1 );

  emp::vector<int> copy;
  const auto num_muts = sgpl::inst_indel_copy(
    std::begin(original), std::end(original),
    std::back_inserter(copy),
    0.1f, 0.5f
  );

  REQUIRE( copy != original );
  REQUIRE( num_muts > 0 );

  // do some of the items in copy come from nowhere in the original?
  REQUIRE( !std::all_of(
    std::begin( copy ), std::end( copy ),
    [&original](const int val){
      return std::find(
        std::begin( original ), std::end( original ),
        val
      ) != std::end( original );
    }
  ) );

}
