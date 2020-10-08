#pragma once

#include <tuple>

#include "../config/Spec.hpp"
#include "../hardware/Cpu.hpp"
#include "../program/Program.hpp"
#include "../utility/EmptyType.hpp"

#include "execute_core.hpp"

namespace sgpl {

template<typename Spec>
inline void execute_cpu(
  const size_t cycles,
  sgpl::Cpu<Spec>& state,
  const sgpl::Program<Spec>& program,
  typename Spec::peripheral_t& peripheral
) {

  for (size_t i{}; i < cycles && state.GetNumCores(); ++i) {

    sgpl::Core<Spec>& core{ state.GetActiveCore() };
    execute_core<Spec>(core, program, peripheral);
    if ( core.HasTerminated() ) state.KillActiveCore();
    else state.ActivateNextCore();
  }

}

template<typename Spec=sgpl::Spec<>>
inline void execute_cpu(
  const size_t cycles,
  sgpl::Cpu<Spec>& state,
  const sgpl::Program<Spec>& program
) {

  using peripheral_t = typename Spec::peripheral_t;
  peripheral_t peripheral;

  for (size_t i{}; i < cycles && state.GetNumCores(); ++i) {

    sgpl::Core<Spec>& core{ state.GetActiveCore() };
    execute_core<Spec>(core, program, peripheral);
    if ( core.HasTerminated() ) state.KillActiveCore();
    else state.ActivateNextCore();
  }

}

} // namespace sgpl
