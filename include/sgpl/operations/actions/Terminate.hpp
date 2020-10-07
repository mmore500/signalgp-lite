#pragma once

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct Terminate {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core,
    const sgpl::Instruction<Library>& inst,
    const sgpl::Program<Library>& program
  ) {
    core.Terminate();
  }

};

} // namespace sgpl
