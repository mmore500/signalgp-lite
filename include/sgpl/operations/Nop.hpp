#pragma once

#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

struct Nop {

  static void run(sgpl::Core& core, const sgpl::Instruction& inst) { ; }

};

} // namespace sgpl
