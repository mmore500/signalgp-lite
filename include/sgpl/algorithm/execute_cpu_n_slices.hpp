#pragma once
#ifndef SGPL_ALGORITHM_EXECUTE_CPU_N_SLICES_HPP_INCLUDE
#define SGPL_ALGORITHM_EXECUTE_CPU_N_SLICES_HPP_INCLUDE

#include <cassert>
#include <cstddef>
#include <tuple>

#include "../hardware/Cpu.hpp"
#include "../program/Program.hpp"
#include "../spec/Spec.hpp"
#include "../utility/EmptyType.hpp"

#include "execute_core_slice.hpp"

namespace sgpl {

template<typename Spec>
void execute_cpu_n_slices(
  const size_t max_slices,
  sgpl::Cpu<Spec>& state,
  const sgpl::Program<Spec>& program,
  typename Spec::peripheral_t& peripheral
) {

  assert( program.size() );

  for (size_t s{}; s < max_slices && state.HasActiveCore(); ++s) {

    auto& core = state.GetActiveCore();
    const size_t num_cycles = execute_core_slice<Spec>(
      core,
      program,
      peripheral
    );
    state.AdvanceCycleClock( num_cycles );
    if ( core.HasTerminated() ) state.KillActiveCore();

    state.TryActivateNextCore();
  }

}

template<typename Spec=sgpl::Spec<>>
inline void execute_cpu_n_slices(
  const size_t max_slices,
  sgpl::Cpu<Spec>& state,
  const sgpl::Program<Spec>& program
) {

  using peripheral_t = typename Spec::peripheral_t;
  peripheral_t peripheral;

  execute_cpu_n_slices<Spec>( max_slices, state, program, peripheral );

}

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_EXECUTE_CPU_N_SLICES_HPP_INCLUDE
