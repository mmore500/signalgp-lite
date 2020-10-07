#pragma once

#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

struct JumpIfLocal {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core, const sgpl::Instruction<Library>& inst
  ) {
    if ( core.registers[ inst.args[0] ] ) {
      core.JumpToLocalAnchorMatch( inst.tag );
    }
  }

};

} // namespace sgpl
