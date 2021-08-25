#pragma once

#include <functional>

#include "conduit/include/uitsl/polyfill/bit_cast.hpp"

namespace bc {

struct SetState {

  template<typename Spec>
  static void run(
      sgpl::Core<Spec>& core,
      const sgpl::Instruction<Spec>& inst,
      const sgpl::Program<Spec>&,
      typename Spec::peripheral_t& peripheral
  ) {
    const size_t a = inst.args[0];
    peripheral.output = std::bit_cast<uint32_t>(core.registers[a]);
  }

  static std::string name() { return "SetState"; }

  static size_t prevalence() { return 10; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& ) {
    return std::map<std::string, std::string>{};
  }

};

} // namespace bc