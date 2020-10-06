#pragma once

#include <tuple>

#include "../hardware/Cpu.hpp"
#include "../program/Program.hpp"

#include "execute_core.hpp"

namespace sgpl {

template<typename Library>
inline void execute_cpu(size_t cycles, Cpu& state, const Program& program) {

  for (size_t i{}; i < cycles && state.GetActiveCoreOrNullptr(); ++i) {
    advance_core<Library>(16, *state.GetActiveCoreOrNullptr(), program);
    state.ActivateNextCore();
  }

}

} // namespace sgpl
