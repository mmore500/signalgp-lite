#pragma once
#ifndef SGPL_OPERATIONS_FLOW_GLOBAL_REGULATORGET_HPP_INCLUDE
#define SGPL_OPERATIONS_FLOW_GLOBAL_REGULATORGET_HPP_INCLUDE

#include <limits>

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace global {

struct RegulatorGet {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {

    for ( const auto uid : core.GetGlobalJumpTable().MatchRaw(inst.tag) ) {
      // (+) values down regulate
      // (-) values up regulate
      core.registers[ inst.args[0] ]
        = core.GetGlobalJumpTable().ViewRegulator(
        uid
      );
      break; // only process first value
    }

  }

  static std::string name() { return "global::RegulatorGet"; }

  static size_t prevalence() { return 1; }

};

} // namespace global
} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_FLOW_GLOBAL_REGULATORGET_HPP_INCLUDE
