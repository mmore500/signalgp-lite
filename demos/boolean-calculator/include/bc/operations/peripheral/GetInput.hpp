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

struct GetInput {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t& peripheral
  ) {
    // std::cout << name() << " ";
    const size_t a = inst.args[0];
    core.registers[a] = std::bit_cast<float>( peripheral.input );
  }

  static std::string name() { return "GetInput"; }

  static size_t prevalence() { return 10; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& ) {
    return std::map<std::string, std::string>{};
  }

};

} // namespace bc
