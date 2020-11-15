#pragma once
#ifndef SGPL_OPERATIONS_FLOW_LOCAL_ANCHOR_HPP_INCLUDE
#define SGPL_OPERATIONS_FLOW_LOCAL_ANCHOR_HPP_INCLUDE

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

  static std::string name() { return "local::Anchor"; }

  static size_t prevalence() { return 10; }

};

} // namespace local
} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_FLOW_LOCAL_ANCHOR_HPP_INCLUDE
