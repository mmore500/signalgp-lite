#pragma once
#ifndef SGPL_OPERATIONS_MEMORY_FIXEDCOPYREGISTER_HPP_INCLUDE
#define SGPL_OPERATIONS_MEMORY_FIXEDCOPYREGISTER_HPP_INCLUDE

#include <map>
#include <set>
#include <string>

#include "../../../../third-party/Empirical/include/emp/tools/string_utils.hpp"

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

/**
 * Copys value of `reg[b]` into `reg[a]`.
 */
struct FixedCopyRegister {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) noexcept {
    const size_t a = inst.args[0], b = inst.args[1];

    core.registers[a] = core.registers[b];

  }

  static std::string name() { return "Fixed Copy Register"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& inst ) {

    return std::map<std::string, std::string>{
      { "argument a", emp::to_string( static_cast<int>( inst.args[0] ) ) },
      { "argument b", emp::to_string( static_cast<int>( inst.args[1] ) ) },
      { "argument c", emp::to_string( static_cast<int>( inst.args[2] ) ) },
      { "summary", "reg[a] = reg[b]" },
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


#endif // #ifndef SGPL_OPERATIONS_MEMORY_FIXEDCOPYREGISTER_HPP_INCLUDE
