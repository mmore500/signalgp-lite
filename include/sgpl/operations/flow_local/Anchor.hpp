#pragma once
#ifndef SGPL_OPERATIONS_FLOW_LOCAL_ANCHOR_HPP_INCLUDE
#define SGPL_OPERATIONS_FLOW_LOCAL_ANCHOR_HPP_INCLUDE

#include <map>
#include <string>

#include "../../../../third-party/Empirical/source/tools/hash_namify.h"
#include "../../../../third-party/Empirical/source/tools/string_utils.h"

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace local {

struct Anchor {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) { ; }

  static std::string name() { return "Local Anchor"; }

  static size_t prevalence() { return 10; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& inst ) {

    using tag_t = typename Spec::tag_t;

    return std::map<std::string, std::string>{
      { "summary", "register a local jump-to destination" },
      { "tag bits", emp::to_string( inst.tag ) },
      { "tag moniker", emp::hash_namify( std::hash< tag_t >{}( inst.tag ) ) },
    };
  }

};

} // namespace local
} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_FLOW_LOCAL_ANCHOR_HPP_INCLUDE
