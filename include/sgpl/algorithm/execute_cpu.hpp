#pragma once

#include <tuple>

#include "../hardware/Cpu.hpp"
#include "../program/Program.hpp"

#include "execute_core.hpp"

namespace sgpl {

template<typename Library>
inline void execute_cpu(
  const size_t cycles,
  sgpl::Cpu<Library>& state,
  const sgpl::Program<Library>& program
) {

  for (size_t i{}; i < cycles && state.GetNumCores(); ++i) {

    sgpl::Core<Library>& core{ state.GetActiveCore() };
    execute_core<Library>(core, program);
    if ( core.HasTerminated() ) state.KillActiveCore();
    else state.ActivateNextCore();
  }

}

} // namespace sgpl
