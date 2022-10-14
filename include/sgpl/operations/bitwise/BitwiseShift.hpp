#pragma once
#ifndef SGPL_OPERATIONS_BITWISE_BITWISESHIFT_HPP_INCLUDE
#define SGPL_OPERATIONS_BITWISE_BITWISESHIFT_HPP_INCLUDE

#include <cstddef>
#include <cstring>
#include <map>
#include <set>
#include <string>

#include "../../../../third-party/conduit/include/uitsl/algorithm/clamp_cast.hpp"
#include "../../../../third-party/conduit/include/uitsl/polyfill/bit_cast.hpp"
#include "../../../../third-party/conduit/include/uit_emp/tools/string_utils.hpp"

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

/**
 * Shifts the bits of `reg[arg_1]` by `reg[arg_2]` positions.
 *
 * (If `reg[arg_2]` is negative, this is a right shift. Otherwise it is a left
 * shift.) Stores the result in `reg[arg_0]`.
 */
struct BitwiseShift {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) noexcept {
    const size_t a = inst.args[0], b = inst.args[1], c = inst.args[2];

    static_assert( sizeof(core.registers[b]) == sizeof(uint32_t) );
    const uint32_t as_uint32{
      std::bit_cast<uint32_t>(core.registers[b])
    };

    constexpr size_t num_bits = sizeof(core.registers[b]) * 8;

    const uint32_t result = ( core.registers[c] > 0 )
      ? std::bitset<num_bits>( as_uint32 ).operator<<(
          uitsl::clamp_cast<size_t>( core.registers[c] )
        ).to_ulong()
      : std::bitset<num_bits>( as_uint32 ).operator>>(
          uitsl::clamp_cast<size_t>( -core.registers[c] )
        ).to_ulong()
      ;

    core.registers[a] = std::bit_cast<float>(result);
  }

  static std::string name() { return "Bitwise Shift"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& inst ) {

    return std::map<std::string, std::string>{
      { "argument a", uit_emp::to_string( static_cast<int>( inst.args[0] ) ) },
      { "argument b", uit_emp::to_string( static_cast<int>( inst.args[1] ) ) },
      { "argument c", uit_emp::to_string( static_cast<int>( inst.args[2] ) ) },
      { "summary", "a = b << c" },
    };
  }

  template<typename Spec>
  static std::set<std::string> categories(const sgpl::Instruction<Spec>&) {
    return {
      "bitwise",
      "calculation",
      "intrinsic",
      "op",
    };
  }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_BITWISE_BITWISESHIFT_HPP_INCLUDE
