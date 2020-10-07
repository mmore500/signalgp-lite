#pragma once

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct Not {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core,
    const sgpl::Instruction<Library>& inst,
    const sgpl::Program<Library>&
  ) {
    core.registers[ inst.args[0] ] = !core.registers[ inst.args[0] ];
  }

};

} // namespace sgpl
