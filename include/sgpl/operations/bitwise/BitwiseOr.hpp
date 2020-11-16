#pragma once
#ifndef SGPL_OPERATIONS_BITWISE_BITWISEOR_HPP_INCLUDE
#define SGPL_OPERATIONS_BITWISE_BITWISEOR_HPP_INCLUDE

#include <cstddef>

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct BitwiseOr {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    const size_t a = inst.args[0], b = inst.args[1], c = inst.args[2];

    std::transform(
      reinterpret_cast<std::byte*>( &core.registers[a] ),
      reinterpret_cast<std::byte*>( &core.registers[a] )
        + sizeof( core.registers[a] ),
      reinterpret_cast<std::byte*>( &core.registers[b] ),
      reinterpret_cast<std::byte*>( &core.registers[c] ),
      [](const std::byte a, const std::byte b){ return a | b; }
    );
  }

  static std::string name() { return "Bitwise Or"; }

  static size_t prevalence() { return 1; }

  static size_t num_registers_to_print() { return 3; }

  static bool should_print_tag() { return false; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_BITWISE_BITWISEOR_HPP_INCLUDE
