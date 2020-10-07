#pragma once

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

#include "../actions/Terminate.hpp"

namespace sgpl {
namespace global {

struct Anchor {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core,
    const sgpl::Instruction<Library>& inst,
    const sgpl::Program<Library>& program
  ) {
    if ( core.HasLocalAnchors() ) {
      sgpl::Terminate::template run<Library>(core, inst, program);
    } else core.LoadLocalAnchors( program );
  }

};

} // namespace global
} // namespace sgpl
