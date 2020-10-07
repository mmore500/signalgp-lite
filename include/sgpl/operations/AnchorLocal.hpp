#pragma once

#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"

#include "Nop.hpp"

namespace sgpl {

struct AnchorLocal {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core, const sgpl::Instruction<Library>& inst
  ) { sgpl::Nop::template run<Library>(core, inst); }

};

} // namespace sgpl
