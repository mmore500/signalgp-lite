#pragma once

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace global {

struct JumpIfNot {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core,
    const sgpl::Instruction<Library>& inst,
    const sgpl::Program<Library>&
  ) {
    if ( !core.registers[ inst.args[0] ] ) {
      core.JumpToGlobalAnchorMatch( inst.tag );
    }
  }

};

} // namespace global
} // namespace sgpl
