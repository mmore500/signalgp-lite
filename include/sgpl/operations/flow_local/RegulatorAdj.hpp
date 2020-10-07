#pragma once

#include <limits>

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace local {

struct RegulatorAdj {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core,
    const sgpl::Instruction<Library>& inst,
    const sgpl::Program<Library>&
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
