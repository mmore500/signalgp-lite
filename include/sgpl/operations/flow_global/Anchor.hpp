#pragma once

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

#include "../actions/Terminate.hpp"

namespace sgpl {
namespace global {

struct Anchor {

  template<typename Library, typename Peripheral>
  static void run(
    sgpl::Core<Library>& core,
    const sgpl::Instruction<Library>& inst,
    const sgpl::Program<Library>& program,
    Peripheral&
  ) {
    if ( core.HasLocalAnchors() ) {
      sgpl::Terminate::template run<Library>(core, inst, program);
    } else core.LoadLocalAnchors( program );
  }

};

} // namespace global
} // namespace sgpl
