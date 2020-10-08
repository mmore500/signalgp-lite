#pragma once

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct Modulo {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
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
