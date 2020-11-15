#pragma once
#ifndef SGPL_OPERATIONS_FLOW_LOCAL_REGULATORSET_HPP_INCLUDE
#define SGPL_OPERATIONS_FLOW_LOCAL_REGULATORSET_HPP_INCLUDE

#include <limits>

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace local {

struct RegulatorSet {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {

    for ( const auto uid : core.GetLocalJumpTable().MatchRaw(inst.tag) ) {
      // (+) values down regulate
      // (-) values up regulate
      core.GetLocalJumpTable().SetRegulator(
        uid,
        core.registers[ inst.args[0] ]
      );
    }

  }

  static std::string name() { return "local::RegulatorSet"; }

  static size_t prevalence() { return 1; }

};

} // namespace local
} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_FLOW_LOCAL_REGULATORSET_HPP_INCLUDE
