#pragma once

#include <tuple>

#include "../hardware/Cpu.hpp"
#include "../program/Program.hpp"
#include "../utility/EmptyType.hpp"

#include "execute_core.hpp"

namespace sgpl {

template<typename Library, typename Peripheral>
inline void execute_cpu(
  const size_t cycles,
  sgpl::Cpu<Library>& state,
  const sgpl::Program<Library>& program,
  Peripheral& peripheral
) {

  for (size_t i{}; i < cycles && state.GetNumCores(); ++i) {

    sgpl::Core<Library>& core{ state.GetActiveCore() };
    execute_core<Library>(core, program, peripheral);
    if ( core.HasTerminated() ) state.KillActiveCore();
    else state.ActivateNextCore();
  }

}

template<typename Library, typename Peripheral=sgpl::EmptyType>
inline void execute_cpu(
  const size_t cycles,
  sgpl::Cpu<Library>& state,
  const sgpl::Program<Library>& program
) {

  Peripheral peripheral;

  for (size_t i{}; i < cycles && state.GetNumCores(); ++i) {

    sgpl::Core<Library>& core{ state.GetActiveCore() };
    execute_core<Library>(core, program, peripheral);
    if ( core.HasTerminated() ) state.KillActiveCore();
    else state.ActivateNextCore();
  }

}

} // namespace sgpl
