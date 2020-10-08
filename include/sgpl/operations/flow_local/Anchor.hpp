#pragma once

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace local {

struct Anchor {

  template<typename Library, typename Peripheral>
  static void run(
    sgpl::Core<Library>& core,
    const sgpl::Instruction<Library>& inst,
    const sgpl::Program<Library>&,
    Peripheral&
  ) { ; }

};

} // namespace local
} // namespace sgpl
