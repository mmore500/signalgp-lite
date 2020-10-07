#pragma once

#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

struct JumpIfGlobal {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core, const sgpl::Instruction<Library>& inst
  ) {
    if ( core.registers[ inst.args[0] ] ) {
      core.JumpToGlobalAnchorMatch( inst.tag );
    }
  }

};

} // namespace sgpl
