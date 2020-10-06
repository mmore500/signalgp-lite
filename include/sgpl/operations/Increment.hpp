#pragma once

#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

struct Increment {

  static void run(sgpl::Core& core, const sgpl::Instruction& inst) {
    ++core.registers[ inst.args[0] ];
  }

};

} // namespace sgpl
