#pragma once
#ifndef SGPL_UTILITY_GARBLEDOUTPUTITERATOR_HPP_INCLUDE
#define SGPL_UTILITY_GARBLEDOUTPUTITERATOR_HPP_INCLUDE

#include <iterator>
#include <type_traits>

#include "../../../third-party/conduit/include/uit_emp/math/Random.hpp"

#include "ThreadLocalRandom.hpp"

namespace sgpl {

// if emp::Random constructor available, inject items so constructed as garble
// otherwise, inject default-constructed items
template<typename OutputIterator>
class GarbledOutputIterator
: protected OutputIterator {

  using parent_t = OutputIterator;
  using container_value_type = typename parent_t::container_type::value_type;

  int remaining_garble{};

public:

  GarbledOutputIterator(
    const OutputIterator& out
  ) : parent_t(out)
  {}

  void AddGarble(int amount) {
    remaining_garble = std::max(
      remaining_garble + amount, 0
    );
  }

  using container_type = typename parent_t::container_type;
  using value_type = typename parent_t::value_type;
  using pointer = typename parent_t::pointer;
  using reference = typename parent_t::reference;
  using iterator_category = std::output_iterator_tag;
  using difference_type = typename parent_t::difference_type;

  GarbledOutputIterator& operator*() { return *this; }

  GarbledOutputIterator& operator->() { return *this; }

  GarbledOutputIterator& operator++() { return *this; }

  GarbledOutputIterator& operator++(int) { return *this; }

  GarbledOutputIterator& operator=( const container_value_type& value ) {
    if (remaining_garble) {
      --remaining_garble;
      parent_t::operator=( [](){
        using cov_t = container_value_type;
        // prefer random constructor, fallback to default constructor
        if constexpr ( std::is_constructible_v<cov_t, uit_emp::Random&> ) {
          return cov_t( sgpl::tlrand.Get() );
        } else return cov_t{};
      }() );
    } else parent_t::operator=( value );
    return *this;
  }

};

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_GARBLEDOUTPUTITERATOR_HPP_INCLUDE
