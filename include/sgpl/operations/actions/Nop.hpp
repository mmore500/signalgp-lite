#pragma once
#ifndef SGPL_OPERATIONS_ACTIONS_NOP_HPP_INCLUDE
#define SGPL_OPERATIONS_ACTIONS_NOP_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct Nop {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>& program,
    typename Spec::peripheral_t&
  ) { ; }

  static std::string name() { return "Nop"; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_ACTIONS_NOP_HPP_INCLUDE
