#pragma once
#ifndef SGPL_PROGRAM_GLOBALANCHORITERATOR_HPP_INCLUDE
#define SGPL_PROGRAM_GLOBALANCHORITERATOR_HPP_INCLUDE

#include <iterator>

#include "../../../third-party/Empirical/source/base/vector.h"

#include "Instruction.hpp"

namespace sgpl {

template<typename Spec>
class GlobalAnchorIterator
: protected emp::vector<sgpl::Instruction<Spec>>::const_iterator {

  using inst_t = sgpl::Instruction<Spec>;
  using library_t = typename Spec::library_t;
  using parent_t
    = typename emp::vector<sgpl::Instruction<Spec>>::const_iterator;

  parent_t end;

public:

  GlobalAnchorIterator(
    const parent_t& init,
    const parent_t& end_
  ) : parent_t(init)
  , end(end_)
  {}

  using value_type = inst_t;
  using pointer = value_type*;
  using reference = value_type&;
  using iterator_category = std::forward_iterator_tag;
  using difference_type = typename parent_t::difference_type;

  const value_type& operator*() { return parent_t::operator*(); }

  const value_type* operator->() { return &operator*(); }

  GlobalAnchorIterator& operator++() {
    do parent_t::operator++();
    while (
      !library_t::IsAnchorLocalOpCode( parent_t::operator*().op_code )
      && *this != end
    );
    // std::cout << "thru" << std::endl;
    return *this;
  }

  GlobalAnchorIterator operator++(int) {
    const auto res = *this;
    operator++();
    return res;
  }

  bool operator==(const GlobalAnchorIterator& other) const {
    return static_cast<parent_t>( *this ) == static_cast<parent_t>( other );
  }

  bool operator!=(const GlobalAnchorIterator& other) const {
    return static_cast<parent_t>( *this ) != static_cast<parent_t>( other );
  }
};

} // namespace sgpl

#endif // #ifndef SGPL_PROGRAM_GLOBALANCHORITERATOR_HPP_INCLUDE
