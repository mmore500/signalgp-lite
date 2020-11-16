#pragma once
#ifndef SGPL_OPERATIONS_BINARY_MODULO_HPP_INCLUDE
#define SGPL_OPERATIONS_BINARY_MODULO_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct Modulo {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    const size_t a = inst.args[0], b = inst.args[1], c = inst.args[2];

    // TODO refactor this into a library call

    const float in_val = core.registers[b];
    const float mod_val = core.registers[c];

    const float remain = std::remainder(in_val, mod_val);

    // mod by zero allowed
    core.registers[a] = (remain < 0.0) ? (remain + mod_val) : remain;
  }

  static std::string name() { return "Modulo"; }

  static size_t prevalence() { return 1; }

  static size_t num_registers_to_print() { return 3; }

  static bool should_print_tag() { return false; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_BINARY_MODULO_HPP_INCLUDE
