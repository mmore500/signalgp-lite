#pragma once
#ifndef SGPL_INTROSPECTION_GET_MODULE_POS_HPP_INCLUDE
#define SGPL_INTROSPECTION_GET_MODULE_POS_HPP_INCLUDE

#include <cassert>
#include <iterator>

#include "../program/GlobalAnchorIterator.hpp"
#include "../program/Program.hpp"

#include "count_modules.hpp"

namespace sgpl {

template<typename Spec>
size_t get_module_pos(
  const sgpl::Program<Spec>& program,
  const size_t module_idx
) {

  assert( module_idx < sgpl::count_modules( program ) );

  const size_t raw_distance = std::distance(
    std::next(
      sgpl::GlobalAnchorIterator<Spec>::make_begin( program ),
      module_idx
    ).begin(),
    std::begin( program )
  );

  return raw_distance;

}

} // namespace sgpl

#endif // #ifndef SGPL_INTROSPECTION_GET_MODULE_POS_HPP_INCLUDE
