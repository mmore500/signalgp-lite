#pragma once
#ifndef SGPL_OPERATIONS_UNARY_NEGATE_HPP_INCLUDE
#define SGPL_OPERATIONS_UNARY_NEGATE_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct Negate {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    core.registers[ inst.args[0] ] = -core.registers[ inst.args[0] ];
  }

  static std::string name() { return "Negate"; }

  static size_t prevalence() { return 1; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_UNARY_NEGATE_HPP_INCLUDE
