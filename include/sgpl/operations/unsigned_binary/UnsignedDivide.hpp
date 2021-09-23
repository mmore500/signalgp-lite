#pragma once
#ifndef SGPL_OPERATIONS_UNSIGNED_BINARY_UNSIGNEDDIVIDE_HPP_INCLUDE
#define SGPL_OPERATIONS_UNSIGNED_BINARY_UNSIGNEDDIVIDE_HPP_INCLUDE

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
 * Divides `reg[arg_1]` by `reg[arg_2]` and stores the result in `reg[arg_0]`.
 *
 * Division by zero can result in an `Inf` or `NaN` value.
 */
struct UnsignedDivide {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) noexcept {
    const size_t a = inst.args[0], b = inst.args[1], c = inst.args[2];
    // division by zero not allowed
    const uint32_t result = (
      std::bit_cast<uint32_t>(core.registers[b])
      / std::max((uint32_t)1, std::bit_cast<uint32_t>(core.registers[c]))
    );
    core.registers[a] = std::bit_cast<float>(result);
  }

  static std::string name() { return "UnsignedDivide"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& inst ) {

    return std::map<std::string, std::string>{
      { "argument a", emp::to_string( static_cast<int>( inst.args[0] ) ) },
      { "argument b", emp::to_string( static_cast<int>( inst.args[1] ) ) },
      { "argument c", emp::to_string( static_cast<int>( inst.args[2] ) ) },
      { "summary", "a = b / c" },
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

#endif // #ifndef SGPL_OPERATIONS_UNSIGNED_BINARY_UNSIGNEDDIVIDE_HPP_INCLUDE
