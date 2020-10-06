#pragma once

#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

struct Terminate {

  static void run(sgpl::Core& core, const sgpl::Instruction& inst) {
    core.Terminate();
  }

};

} // namespace sgpl
