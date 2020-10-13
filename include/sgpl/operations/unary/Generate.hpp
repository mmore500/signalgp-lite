#pragma once
#ifndef SGPL_OPERATIONS_UNARY_GENERATE_HPP_INCLUDE
#define SGPL_OPERATIONS_UNARY_GENERATE_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"
#include "../../utility/ThreadLocalRandom.hpp"

namespace sgpl {

struct Generate {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    core.registers[ inst.args[0] ] = sgpl::ThreadLocalRandom::Get().GetDouble();
  }

  static std::string name() { return "Generate"; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_UNARY_GENERATE_HPP_INCLUDE
