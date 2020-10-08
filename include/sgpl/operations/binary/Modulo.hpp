#pragma once

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct Modulo {

  template<typename Library, typename Peripheral>
  static void run(
    sgpl::Core<Library>& core,
    const sgpl::Instruction<Library>& inst,
    const sgpl::Program<Library>&,
    Peripheral&
  ) {
    const size_t a = inst.args[0], b = inst.args[1], c = inst.args[2];

    // TODO refactor this into a library call

    const float in_val = core.registers[b];
    const float mod_val = core.registers[c];

    const float remain = std::remainder(in_val, mod_val);
    core.registers[a] = (remain < 0.0) ? (remain + mod_val) : remain;
  }

};

} // namespace sgpl
