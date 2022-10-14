#pragma once
#ifndef SGPL_ALGORITHM_EXECUTE_CPU_N_CYCLES_HPP_INCLUDE
#define SGPL_ALGORITHM_EXECUTE_CPU_N_CYCLES_HPP_INCLUDE

#include <algorithm>
#include <cassert>

#include "../hardware/Cpu.hpp"
#include "../program/Program.hpp"
#include "../spec/Spec.hpp"
#include "../utility/EmptyType.hpp"

#include "execute_core.hpp"

namespace sgpl {

template<typename Spec>
void execute_cpu_n_cycles(
  const size_t max_cycles,
  sgpl::Cpu<Spec>& state,
  const sgpl::Program<Spec>& program,
  typename Spec::peripheral_t& peripheral
) {

  assert( program.size() );

  for (size_t c{}; c < max_cycles && state.HasActiveCore(); /*incr c inside*/) {

    auto& core = state.GetActiveCore();
    const size_t try_cycles = std::min(Spec::switch_steps, max_cycles - c);
    const size_t res_cycles = execute_core_cycles<Spec>(
      core,
      program,
      peripheral,
      try_cycles
    );
    state.AdvanceCycleClock( res_cycles );
    c += res_cycles;
    if ( core.HasTerminated() ) state.KillActiveCore();

    state.TryActivateNextCore();
  }

}

template<typename Spec=sgpl::Spec<>>
inline void execute_cpu_n_cycles(
  const size_t cycles,
  sgpl::Cpu<Spec>& state,
  const sgpl::Program<Spec>& program
) {

  using peripheral_t = typename Spec::peripheral_t;
  peripheral_t peripheral;

  execute_cpu_n_cycles<Spec>( cycles, state, program, peripheral );

}

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_EXECUTE_CPU_N_CYCLES_HPP_INCLUDE
