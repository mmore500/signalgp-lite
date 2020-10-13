#pragma once
#ifndef SGPL_OPERATIONS_FLOW_GLOBAL_ANCHOR_HPP_INCLUDE
#define SGPL_OPERATIONS_FLOW_GLOBAL_ANCHOR_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

#include "../actions/Terminate.hpp"

namespace sgpl {
namespace global {

struct Anchor {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>& program,
    typename Spec::peripheral_t& peripheral
  ) {
    if ( core.HasLocalAnchors() ) {
      sgpl::Terminate::template run<Spec>(core, inst, program, peripheral);
    } else core.LoadLocalAnchors( program );
  }

  static std::string name() { return "global::Anchor"; }

};

} // namespace global
} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_FLOW_GLOBAL_ANCHOR_HPP_INCLUDE
