#pragma once
#ifndef SGPL_ALGORITHM_EXECUTE_CORE_SLICE_HPP_INCLUDE
#define SGPL_ALGORITHM_EXECUTE_CORE_SLICE_HPP_INCLUDE

#include "execute_core_cycles.hpp"

namespace sgpl {

template<typename Spec>
inline size_t execute_core_slice(
  sgpl::Core<Spec>& state,
  const sgpl::Program<Spec>& program,
  typename Spec::peripheral_t& peripheral
) {

  return execute_core_cycles(state, program, peripheral, Spec::switch_steps);

};

template<typename Spec>
inline size_t execute_core_slice(
  sgpl::Core<Spec>& state,
  const sgpl::Program<Spec>& program
) {

  using peripheral_t = typename Spec::peripheral_t;
  peripheral_t peripheral;

  return execute_core_slice<Spec>(state, program, peripheral);

}


} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_EXECUTE_CORE_SLICE_HPP_INCLUDE
