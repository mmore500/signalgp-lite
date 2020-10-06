#pragma once

#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

struct Decrement {

  static void run(Core& core, const Instruction& inst) {
    --core.registers[ inst.args[0] ];
  }

};

} // namespace sgpl
