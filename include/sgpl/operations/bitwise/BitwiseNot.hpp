#pragma once
#ifndef SGPL_OPERATIONS_BITWISE_BITWISENOT_HPP_INCLUDE
#define SGPL_OPERATIONS_BITWISE_BITWISENOT_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

#include <cstddef>

namespace sgpl {

struct BitwiseNot {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    const size_t a = inst.args[0], b = inst.args[1];

    std::transform(
      reinterpret_cast<std::byte*>( &core.registers[a] ),
      reinterpret_cast<std::byte*>( &core.registers[a] )
        + sizeof( core.registers[a] ),
      reinterpret_cast<std::byte*>( &core.registers[b] ),
      [](const std::byte a){ return ~a; }
    );
  }

  static std::string name() { return "Bitwise Not"; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_BITWISE_BITWISENOT_HPP_INCLUDE
