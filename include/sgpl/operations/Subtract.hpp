#pragma once

#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

struct Subtract {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core, const sgpl::Instruction<Library>& inst
  ) {
    double& a = core.registers[ inst.args[0] ];
    const double& b = core.registers[ inst.args[1] ];
    const double& c = core.registers[ inst.args[2] ];
    a = b - c;
  }

};

} // namespace sgpl
