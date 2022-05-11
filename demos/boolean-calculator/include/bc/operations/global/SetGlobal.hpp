#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <map>
#include <set>
#include <string>

#include "Empirical/include/emp/tools/string_utils.hpp"

#include "conduit/include/uitsl/polyfill/bit_cast.hpp"

#include "sgpl/hardware/Core.hpp"
#include "sgpl/program/Instruction.hpp"
#include "sgpl/program/Program.hpp"


namespace bc {

struct SetGlobal {
  template<typename Spec>
  static void run(
      sgpl::Core<Spec>& core,
      const sgpl::Instruction<Spec>& inst,
      const sgpl::Program<Spec>&,
      typename Spec::peripheral_t& peripheral
  ) {
    const size_t a = inst.args[0];
    const size_t b = inst.args[1];

    peripheral.global_registers[a] = core.registers[b];
  }

  static std::string name() { return "SetGlobal"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& ) {
    return std::map<std::string, std::string>{};
  }
};

} // namespace bc
