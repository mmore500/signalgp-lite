#pragma once

#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

struct Add {

  static void run(Core& core, const Instruction& inst) {
    double& a = core.registers[ inst.args[0] ];
    const double& b = core.registers[ inst.args[1] ];
    const double& c = core.registers[ inst.args[2] ];
    a = b + c;
  }

};

} // namespace sgpl
