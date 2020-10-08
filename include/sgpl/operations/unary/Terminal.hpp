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
  template<typename Library, typename Peripheral>
  static void run(
    sgpl::Core<Library>& core,
    const sgpl::Instruction<Library>& inst,
    const sgpl::Program<Library>&,
    Peripheral&
  ) {
    constexpr double max = static_cast<double>(MaxRatio::num) / MaxRatio::den;
    constexpr double min = static_cast<double>(MinRatio::num) / MinRatio::den;

    const auto& tag = inst.tag;

    const double val = (tag.GetDouble() / tag.MaxDouble()) * (max - min) - min;

    core.registers[ inst.args[0] ] = val;

  }
};

} // namespace sgpl
