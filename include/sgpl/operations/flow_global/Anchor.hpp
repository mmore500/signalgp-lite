#pragma once
#ifndef SGPL_OPERATIONS_FLOW_GLOBAL_ANCHOR_HPP_INCLUDE
#define SGPL_OPERATIONS_FLOW_GLOBAL_ANCHOR_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace global {

struct Anchor {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>& program,
    typename Spec::peripheral_t& peripheral
  ) {
    if ( core.HasLocalAnchors() ) core.Terminate();
    else core.LoadLocalAnchors( program );
  }

  static std::string name() { return "global::Anchor"; }

  static size_t prevalence() { return 10; }

  static size_t num_registers_to_print() { return 0; }

  static bool should_print_tag() { return false; }

};

} // namespace global
} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_FLOW_GLOBAL_ANCHOR_HPP_INCLUDE
