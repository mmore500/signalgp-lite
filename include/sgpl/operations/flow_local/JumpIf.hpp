#pragma once

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace local {

struct JumpIf {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    if ( core.registers[ inst.args[0] ] ) {
      core.JumpToLocalAnchorMatch( inst.tag );
    }
  }

};

} // namespace local
} // namespace sgpl
