#pragma once
#ifndef SGPL_OPERATIONS_UNARY_COINFLIP_HPP_INCLUDE
#define SGPL_OPERATIONS_UNARY_COINFLIP_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"
#include "../../utility/ThreadLocalRandom.hpp"

namespace sgpl {

struct CoinFlip {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    constexpr double max_double = decltype(inst.tag)::MaxDouble();

    const double p = inst.tag.GetDouble() / max_double;

    core.registers[ inst.args[0] ] = sgpl::ThreadLocalRandom::Get().P( p );

  }

  static std::string name() { return "CoinFlip"; }

  static size_t prevalence() { return 1; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_UNARY_COINFLIP_HPP_INCLUDE
