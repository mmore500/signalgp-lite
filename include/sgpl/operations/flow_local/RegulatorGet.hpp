#pragma once

#include <limits>

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace local {

struct RegulatorGet {

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
      // (+) values down regulate
      // (-) values up regulate
      core.registers[ inst.args[0] ]
        = core.GetLocalJumpTable().ViewRegulator(
        uid
      );
      break; // only process first value
    }

  }

};

} // namespace local
} // namespace sgpl