#pragma once
#ifndef SGPL_UTILITY_CAPPEDOUTPUTITERATOR_HPP_INCLUDE
#define SGPL_UTILITY_CAPPEDOUTPUTITERATOR_HPP_INCLUDE

#include <iterator>
#include <memory>

namespace sgpl {

template<typename OutputIterator>
class CappedOutputIterator
: protected OutputIterator {

  using parent_t = OutputIterator;
  using container_value_type = typename parent_t::container_type::value_type;

  std::shared_ptr<size_t> remaining_capacity;

public:

  CappedOutputIterator(
    const OutputIterator& out,
    const size_t cap
  ) : parent_t(out)
  , remaining_capacity(std::make_shared<size_t>(cap))
  {}

  using container_type = typename parent_t::container_type;
  using value_type = typename parent_t::value_type;
  using pointer = typename parent_t::pointer;
  using reference = typename parent_t::reference;
  using iterator_category = std::output_iterator_tag;
  using difference_type = typename parent_t::difference_type;

  CappedOutputIterator& operator*() { return *this; }

  CappedOutputIterator& operator->() { return *this; }

  CappedOutputIterator& operator++() { return *this; }

  CappedOutputIterator& operator++(int) { return *this; }

  CappedOutputIterator& operator=( const container_value_type& value ) {
    if (*remaining_capacity) {
      parent_t::operator=(value);
      --(*remaining_capacity);
    }
    return *this;
  }

};

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_CAPPEDOUTPUTITERATOR_HPP_INCLUDE
