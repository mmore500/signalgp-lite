#pragma once
#ifndef SGPL_OPERATIONS_BITWISE_RANDOMFILL_HPP_INCLUDE
#define SGPL_OPERATIONS_BITWISE_RANDOMFILL_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"
#include "../../utility/ThreadLocalRandom.hpp"

namespace sgpl {

struct RandomFill {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {

    auto& target = core.registers[ inst.args[0] ];

    sgpl::ThreadLocalRandom::Get().RandFill(
      reinterpret_cast<unsigned char*>( &target ), sizeof( target )
    );

  }

  static std::string name() { return "RandomFill"; }

  static size_t prevalence() { return 1; }

  static size_t num_registers_to_print() { return 1; }

  static bool should_print_tag() { return false; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_BITWISE_RANDOMFILL_HPP_INCLUDE
