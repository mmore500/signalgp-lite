#pragma once

#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"

#include "Terminate.hpp"

namespace sgpl {

struct AnchorGlobal {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core, const sgpl::Instruction<Library>& inst
  ) { sgpl::Terminate::template run<Library>(core, inst); }

};

} // namespace sgpl
