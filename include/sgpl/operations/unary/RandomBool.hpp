#pragma once
#ifndef SGPL_OPERATIONS_UNARY_COINFLIP_HPP_INCLUDE
#define SGPL_OPERATIONS_UNARY_COINFLIP_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"
#include "../../utility/ThreadLocalRandom.hpp"

namespace sgpl {

class RandomBool {

  template<typename Spec>
  static double map_to_unit( const typename Spec::tag_t& tag ) {

    constexpr double max_double = Spec::tag_t::MaxDouble();

    return tag.GetDouble() / max_double;

  }

public:

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {

    const double p = map_to_unit<Spec>( inst.tag );

    core.registers[ inst.args[0] ] = sgpl::ThreadLocalRandom::Get().P( p );

  }

  static std::string name() { return "RandomBool"; }

  static size_t prevalence() { return 1; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_UNARY_COINFLIP_HPP_INCLUDE
