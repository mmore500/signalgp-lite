#pragma once
#ifndef SGPL_OPERATIONS_FLOW_GLOBAL_JUMPIFNOT_HPP_INCLUDE
#define SGPL_OPERATIONS_FLOW_GLOBAL_JUMPIFNOT_HPP_INCLUDE


#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace global {

struct JumpIfNot {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    if ( !core.registers[ inst.args[0] ] ) {
      core.JumpToGlobalAnchorMatch( inst.tag );
    }
    if ( !core.registers[ inst.args[1] ] ) core.ResetRegisters();
  }

  static std::string name() { return "global::JumpIfNot"; }

  static size_t prevalence() { return 1; }

};

} // namespace global
} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_FLOW_GLOBAL_JUMPIFNOT_HPP_INCLUDE
