#pragma once
#ifndef SGPL_ALGORITHM_EXECUTE_CPU_HPP_INCLUDE
#define SGPL_ALGORITHM_EXECUTE_CPU_HPP_INCLUDE

#include <cstddef>

#include "execute_cpu_n_slices.hpp"

namespace sgpl {

template<typename Spec>
[[deprecated("Use execute_cpu_n_slices instead.")]]
inline void execute_cpu(
  const size_t max_slices,
  sgpl::Cpu<Spec>& state,
  const sgpl::Program<Spec>& program,
  typename Spec::peripheral_t& peripheral
) {
  return execute_cpu_n_slices(
    max_slices,
    state,
    program,
    peripheral
  );
}

template<typename Spec>
[[deprecated("Use execute_cpu_n_slices instead.")]]
inline void execute_cpu(
  const size_t max_slices,
  sgpl::Cpu<Spec>& state,
  const sgpl::Program<Spec>& program
) {
  return execute_cpu_n_slices(
    max_slices,
    state,
    program
  );
}

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_EXECUTE_CPU_HPP_INCLUDE
