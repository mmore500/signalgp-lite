#pragma once
#ifndef SGPL_ALGORITHM_EXECUTE_CORE_HPP_INCLUDE
#define SGPL_ALGORITHM_EXECUTE_CORE_HPP_INCLUDE

#include "execute_core_slice.hpp"

namespace sgpl {

template<typename Spec>
[[deprecated("Use execute_core_slice instead.")]]
inline size_t execute_core(
  sgpl::Core<Spec>& state,
  const sgpl::Program<Spec>& program,
  typename Spec::peripheral_t& peripheral
) {
  return execute_core_slice(state, program, peripheral);
};

template<typename Spec>
[[deprecated("Use execute_core_slice instead.")]]
inline size_t execute_core(
  sgpl::Core<Spec>& state,
  const sgpl::Program<Spec>& program
) {
  return execute_core_slice<Spec>(state, program);
}


} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_EXECUTE_CORE_HPP_INCLUDE
