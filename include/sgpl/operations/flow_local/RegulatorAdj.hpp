#pragma once

#include <limits>

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace local {

struct RegulatorAdj {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {

    for ( const auto uid : core.GetLocalJumpTable().MatchRaw(
      inst.tag,
      std::numeric_limits<size_t>::max()
    ) ) {
      core.GetLocalJumpTable().AdjRegulator(
        uid,
        core.registers[ inst.args[0] ]
      );
    }

  }

};

} // namespace local
} // namespace sgpl
