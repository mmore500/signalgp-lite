#pragma once

#include <ratio>

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

template<
  typename MaxRatio=std::ratio<1>,
  typename MinRatio=std::ratio<-1>
>
struct Terminal {

  // writes a genetically-encoded value into a register.
  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    constexpr double max = static_cast<double>(MaxRatio::num) / MaxRatio::den;
    constexpr double min = static_cast<double>(MinRatio::num) / MinRatio::den;

    const auto& tag = inst.tag;

    const double val = (tag.GetDouble() / tag.MaxDouble()) * (max - min) - min;

    core.registers[ inst.args[0] ] = val;

  }
};

} // namespace sgpl
