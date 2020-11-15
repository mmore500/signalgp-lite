#pragma once
#ifndef SGPL_OPERATIONS_BITWISE_SHIFTLEFT_HPP_INCLUDE
#define SGPL_OPERATIONS_BITWISE_SHIFTLEFT_HPP_INCLUDE

#include <cstddef>

#include "../../../../third-party/conduit/include/uitsl/algorithm/clamp_cast.hpp"

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct BitwiseShift {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    const size_t a = inst.args[0], b = inst.args[1], c = inst.args[2];

    static_assert( sizeof(core.registers[a]) <= sizeof(size_t) );
    size_t as_size_t;

    std::memcpy(
      &as_size_t,
      &core.registers[a],
      sizeof( core.registers[a] )
    );

    constexpr size_t num_bits = sizeof(core.registers[a]) * 8;

    const size_t result = ( core.registers[b] > 0 )
      ? std::bitset<num_bits>( as_size_t ).operator<<(
          uitsl::clamp_cast<size_t>( core.registers[b] )
        ).to_ulong()
      : std::bitset<num_bits>( as_size_t ).operator>>(
          uitsl::clamp_cast<size_t>( -core.registers[b] )
        ).to_ulong()
      ;

    std::memcpy(
      &core.registers[c],
      &result,
      sizeof( core.registers[c] )
    );
  }

  static std::string name() { return "Bitwise Shift"; }

  static size_t prevalence() { return 1; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_BITWISE_SHIFTLEFT_HPP_INCLUDE
