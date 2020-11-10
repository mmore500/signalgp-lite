#pragma once
#ifndef SGPL_INTROSPECTION_COUNT_MODULES_HPP_INCLUDE
#define SGPL_INTROSPECTION_COUNT_MODULES_HPP_INCLUDE

#include <iterator>

#include "../program/GlobalAnchorIterator.hpp"
#include "../program/Program.hpp"

namespace sgpl {

template<typename Spec>
size_t count_modules( const Program<Spec>& program ) {

  return std::distance(
    sgpl::GlobalAnchorIterator<Spec>(
      std::begin( program ),
      std::end( program )
    ),
    sgpl::GlobalAnchorIterator<Spec>(
      std::end( program ),
      std::end( program )
    )
  );

}

} // namespace sgpl

#endif // #ifndef SGPL_INTROSPECTION_COUNT_MODULES_HPP_INCLUDE
