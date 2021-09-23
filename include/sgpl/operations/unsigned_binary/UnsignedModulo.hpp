#pragma once
#ifndef SGPL_OPERATIONS_UNSIGNED_BINARY_UNSIGNEDMODULO_HPP_INCLUDE
#define SGPL_OPERATIONS_UNSIGNED_BINARY_UNSIGNEDMODULO_HPP_INCLUDE

#include <algorithm>
#include <map>
#include <set>
#include <string>

#include "../../../../third-party/Empirical/include/emp/tools/string_utils.hpp"

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

/**
 * Calculates the modulus of `reg[arg_1]` by `reg[arg_2]` and stores the result
 * in `reg[arg_0]`.
 *
 * Mod by zero can result in a `NaN` value.
 */
struct UnsignedModulo {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) noexcept {
    const size_t a = inst.args[0], b = inst.args[1], c = inst.args[2];

    // TODO refactor this into a library call

    const uint32_t in_val = std::bit_cast<uint32_t>(core.registers[b]);
    const uint32_t mod_val = std::bit_cast<uint32_t>(core.registers[c]);

    const uint32_t remain = in_val % std::max((uint32_t)1, mod_val);

    // mod by zero allowed
    const uint32_t result = (remain < 0.0) ? (remain + mod_val) : remain;
    core.registers[a] = std::bit_cast<uint32_t>(result);
  }

  static std::string name() { return "UnsignedModulo"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& inst ) {

    return std::map<std::string, std::string>{
      { "argument a", emp::to_string( static_cast<int>( inst.args[0] ) ) },
      { "argument b", emp::to_string( static_cast<int>( inst.args[1] ) ) },
      { "argument c", emp::to_string( static_cast<int>( inst.args[2] ) ) },
      { "summary", "a = b % c" },
    };
  }

  template<typename Spec>
  static std::set<std::string> categories(const sgpl::Instruction<Spec>&) {
    return {
      "calculation",
      "intrinsic",
      "op",
    };
  }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_UNSIGNED_BINARY_UNSIGNEDMODULO_HPP_INCLUDE
