#pragma once
#ifndef SGPL_OPERATIONS_ACTIONS_FORKIF_HPP_INCLUDE
#define SGPL_OPERATIONS_ACTIONS_FORKIF_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct ForkIf {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>& program,
    typename Spec::peripheral_t&
  ) {
    if ( core.registers[ inst.args[0] ] ) core.RequestFork( inst.tag );
  }

  static std::string name() { return "ForkIf"; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_ACTIONS_FORK_HPP_INCLUDE
