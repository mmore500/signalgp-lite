#pragma once
#ifndef SGPL_OPERATIONS_FLOW_LOCAL_REGULATORGET_HPP_INCLUDE
#define SGPL_OPERATIONS_FLOW_LOCAL_REGULATORGET_HPP_INCLUDE

#include <limits>

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace local {

struct RegulatorGet {

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
      core.registers[ inst.args[0] ]
        = core.GetLocalJumpTable().ViewRegulator(
        uid
      );
      break; // only process first value
    }

  }

  static std::string name() { return "local::RegulatorGet"; }

  static size_t prevalence() { return 1; }

  static size_t num_registers_to_print() { return 1; }

  static bool should_print_tag() { return true; }

};

} // namespace local
} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_FLOW_LOCAL_REGULATORGET_HPP_INCLUDE
