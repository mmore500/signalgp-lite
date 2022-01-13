#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/algorithm/module_indel_copy.hpp"
#include "sgpl/utility/CappedOutputIterator.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

template<typename T>
class FalseyAnchorIterator
: public emp::vector<T>::const_iterator {

  using inst_t = T;
  using container_t = emp::vector<T>;
  using parent_t = typename container_t::const_iterator;

  parent_t end_iter;

  FalseyAnchorIterator(
    const parent_t& init,
    const parent_t& end_iter_
  ) : parent_t(init)
  , end_iter(end_iter_)
  {}


public:

  static FalseyAnchorIterator make_begin( const container_t& container ) {
    return FalseyAnchorIterator(
      std::begin( container ),
      std::end( container )
    );
  }

  static FalseyAnchorIterator make_end( const container_t& container ) {
    return FalseyAnchorIterator(
      std::end( container ),
      std::end( container )
    );
  }

  using value_type = inst_t;
  using pointer = value_type*;
  using reference = value_type&;
  using iterator_category = std::forward_iterator_tag;
  using difference_type = typename parent_t::difference_type;

  const value_type& operator*() { return parent_t::operator*(); }

  const value_type* operator->() { return &operator*(); }

  parent_t begin() const { return static_cast<parent_t>( *this ); }
  parent_t end() const { return std::next(*this).begin(); }

  FalseyAnchorIterator& operator++() {

    do {
      parent_t::operator++();
    } while ( *this != end_iter && **this );

    return *this;
  }

  FalseyAnchorIterator operator++(int) {
    const auto res = *this;
    operator++();
    return res;
  }

  bool operator==(const FalseyAnchorIterator& other) const {
    return static_cast<parent_t>( *this ) == static_cast<parent_t>( other );
  }

  bool operator!=(const FalseyAnchorIterator& other) const {
    return static_cast<parent_t>( *this ) != static_cast<parent_t>( other );
  }

};

TEST_CASE("Test module_indel_copy without mutation and with empty source") {

  sgpl::tlrand.Get() = emp::Random(1);

  using container_t = emp::vector<int>;
  container_t original( 0 );

  container_t copy;
  const auto num_muts = sgpl::module_indel_copy(
    FalseyAnchorIterator<int>::make_begin(original),
    FalseyAnchorIterator<int>::make_end(original),
    std::back_inserter(copy),
    0.0f
  );

  REQUIRE( original == copy );
  REQUIRE( num_muts == 0 );

}

TEST_CASE("Test module_indel_copy with mutation and with empty source") {

  sgpl::tlrand.Get() = emp::Random(1);

  using container_t = emp::vector<int>;
  container_t original( 0 );

  container_t copy;
  const auto num_muts = sgpl::module_indel_copy(
    FalseyAnchorIterator<int>::make_begin(original),
    FalseyAnchorIterator<int>::make_end(original),
    std::back_inserter(copy),
    1.0f
  );

  REQUIRE( original == copy );
  REQUIRE( num_muts == 0 );

}

TEST_CASE("Test module_indel_copy without mutation and with anchors") {

  sgpl::tlrand.Get() = emp::Random(1);

  using container_t = emp::vector<int>;
  container_t original( 100 );
  std::iota( std::begin( original ), std::end( original ), 0 );
  // add anchors
  for (size_t i{}; i < original.size(); i += 10 ) original[i] = 0;

  container_t copy;
  const auto num_muts = sgpl::module_indel_copy(
    FalseyAnchorIterator<int>::make_begin(original),
    FalseyAnchorIterator<int>::make_end(original),
    std::back_inserter(copy),
    0.0f
  );

  REQUIRE( original == copy );
  REQUIRE( num_muts == 0 );

}

TEST_CASE("Test module_indel_copy without mutation and no anchors") {

  sgpl::tlrand.Get() = emp::Random(1);

  using container_t = emp::vector<int>;
  container_t original( 100 );
  std::iota( std::begin( original ), std::end( original ), 1 );

  container_t copy;
  const auto num_muts = sgpl::module_indel_copy(
    FalseyAnchorIterator<int>::make_begin(original),
    FalseyAnchorIterator<int>::make_end(original),
    std::back_inserter(copy),
    0.0f
  );

  REQUIRE( original == copy );
  REQUIRE( num_muts == 0 );

}

TEST_CASE("Test module_indel_copy with mutation and anchors") {

  sgpl::tlrand.Get() = emp::Random(1);

  using container_t = emp::vector<size_t>;
  container_t original( 100 );
  std::iota( std::begin( original ), std::end( original ), 0 );
  // add anchors
  for (size_t i{}; i < original.size(); i += 10 ) original[i] = 0;

  container_t copy;
  const auto num_muts = sgpl::module_indel_copy(
    FalseyAnchorIterator<size_t>::make_begin(original),
    FalseyAnchorIterator<size_t>::make_end(original),
    std::back_inserter(copy),
    0.5f
  );

  REQUIRE( copy.size() > 0 );
  REQUIRE( copy.size() < original.size() * 2 );
  REQUIRE( num_muts );

  REQUIRE( !std::equal(
    std::begin(original), std::end(original),
    std::begin(copy), std::end(copy)
  ) );

  // all modules should have shifted position by exactly 10
  // because all modules are 10 long
  REQUIRE( copy.size() % 10 == 0 );
  for (size_t i{}; i < copy.size(); ++i) REQUIRE(
    copy[i] % 10 == i % 10
  );

}

TEST_CASE("Test module_indel_copy with insertion mutation only and anchors") {

  sgpl::tlrand.Get() = emp::Random(1);

  using container_t = emp::vector<size_t>;
  container_t original( 100 );
  std::iota( std::begin( original ), std::end( original ), 0 );
  // add anchors
  for (size_t i{}; i < original.size(); i += 10 ) original[i] = 0;

  container_t copy;
  const auto num_muts = sgpl::module_indel_copy(
    FalseyAnchorIterator<size_t>::make_begin(original),
    FalseyAnchorIterator<size_t>::make_end(original),
    std::back_inserter(copy),
    0.5f, 1.f
  );

  REQUIRE( copy.size() > original.size() );
  REQUIRE( copy.size() < original.size() * 2 );
  REQUIRE( num_muts );

  REQUIRE( !std::equal(
    std::begin(original), std::end(original),
    std::begin(copy), std::end(copy)
  ) );

  // all modules should have shifted position by exactly 10
  // because all modules are 10 long
  REQUIRE( copy.size() % 10 == 0 );
  for (size_t i{}; i < copy.size(); ++i) REQUIRE(
    copy[i] % 10 == i % 10
  );

}

TEST_CASE("Test module_indel_copy with deletion mutation only and anchors") {

  sgpl::tlrand.Get() = emp::Random(1);

  using container_t = emp::vector<size_t>;
  container_t original( 100 );
  std::iota( std::begin( original ), std::end( original ), 0 );
  // add anchors
  for (size_t i{}; i < original.size(); i += 10 ) original[i] = 0;

  container_t copy;
  const auto num_muts = sgpl::module_indel_copy(
    FalseyAnchorIterator<size_t>::make_begin(original),
    FalseyAnchorIterator<size_t>::make_end(original),
    std::back_inserter(copy),
    0.5f, 0.f
  );

  REQUIRE( copy.size() < original.size() );
  REQUIRE( copy.size() );
  REQUIRE( num_muts );

  REQUIRE( !std::equal(
    std::begin(original), std::end(original),
    std::begin(copy), std::end(copy)
  ) );

  // all modules should have shifted position by exactly 10
  // because all modules are 10 long
  REQUIRE( copy.size() % 10 == 0 );
  for (size_t i{}; i < copy.size(); ++i) REQUIRE(
    copy[i] % 10 == i % 10
  );

}

TEST_CASE("Test module_indel_copy with mutation and no anchors") {

  sgpl::tlrand.Get() = emp::Random(1);

  using container_t = emp::vector<size_t>;
  container_t original( 100 );
  std::iota( std::begin( original ), std::end( original ), 1 );

  container_t copy;
  const auto num_muts = sgpl::module_indel_copy(
    FalseyAnchorIterator<size_t>::make_begin(original),
    FalseyAnchorIterator<size_t>::make_end(original),
    std::back_inserter(copy),
    1.f
  );

  REQUIRE( copy.size() >= 0 );
  REQUIRE( copy.size() <= original.size() * 2 );
  REQUIRE( num_muts );

  REQUIRE( !std::equal(
    std::begin(original), std::end(original),
    std::begin(copy), std::end(copy)
  ) );

  // all modules should have shifted position by exactly 10
  // because all modules are 10 long
  REQUIRE( copy.size() % 100 == 0 );
  for (size_t i{}; i < copy.size(); ++i) REQUIRE(
    copy[i] % 100 == (i+1) % 100
  );

}

TEST_CASE("Test module_indel_copy with mutation, anchors, and res limit") {

  sgpl::tlrand.Get() = emp::Random(1);

  using container_t = emp::vector<size_t>;
  container_t original( 100 );
  std::iota( std::begin( original ), std::end( original ), 0 );
  // add anchors
  for (size_t i{}; i < original.size(); i += 10 ) original[i] = 0;

  container_t copy;
  const auto num_muts = sgpl::module_indel_copy(
    FalseyAnchorIterator<size_t>::make_begin(original),
    FalseyAnchorIterator<size_t>::make_end(original),
    sgpl::CappedOutputIterator(std::back_inserter(copy), 57),
    0.5f
  );

  REQUIRE( copy.size() > 0 );
  REQUIRE( copy.size() < original.size() * 2 );
  REQUIRE( num_muts );

  REQUIRE( !std::equal(
    std::begin(original), std::end(original),
    std::begin(copy), std::end(copy)
  ) );

  // all modules should have shifted position by exactly 10
  // because all modules are 10 long
  for (size_t i{}; i < copy.size(); ++i) REQUIRE(
    copy[i] % 10 == i % 10
  );

}
