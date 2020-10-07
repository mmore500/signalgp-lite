#pragma once

#include <limits>

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace global {

struct RegulatorAdj {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core,
    const sgpl::Instruction<Library>& inst,
    const sgpl::Program<Library>&
  ) {

    for ( const auto uid : core.GetGlobalJumpTable().MatchRaw(
      inst.tag,
      std::numeric_limits<size_t>::max()
    ) ) {
      // (+) values down regulate
      // (-) values up regulate
      core.GetGlobalJumpTable().SetRegulator(
        uid,
        core.registers[ inst.args[0] ]
      );
    }

  }

};

} // namespace global
} // namespace sgpl
