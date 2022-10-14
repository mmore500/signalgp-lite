#pragma once
#ifndef SGPL_ALGORITHM_EXECUTE_CORE_CYCLES_HPP_INCLUDE
#define SGPL_ALGORITHM_EXECUTE_CORE_CYCLES_HPP_INCLUDE

#include "../debug/sgpl_assert.hpp"
#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"
#include "../program/Program.hpp"

#include "advance_core.hpp"

namespace sgpl {

template<typename Spec>
inline size_t execute_core_cycles(
  sgpl::Core<Spec>& state,
  const sgpl::Program<Spec>& program,
  typename Spec::peripheral_t& peripheral,
  const size_t max_cycles
) {

  /**
   * We need to make sure that the GlobalJumpTable is populated
   * /except/ when the program has no modules.
   * In this case, when there are no GlobalAnchors within the program,
   * it is acceptable for the GlobalJumpTable to be empty.
   */
  sgpl_assert(
    state.GetGlobalJumpTable().GetSize()
    || !program.HasGlobalAnchor(),
      "Global anchors not initialized! "
      "Hint: call Cpu.InitializeAnchors()"
      << state.GetGlobalJumpTable().GetSize()
      << program.HasGlobalAnchor()
  );

  size_t c;
  for (c = 0; c < max_cycles && !state.HasTerminated(); ++c) {
    advance_core<Spec>(state, program, peripheral);
  }
  return c;

};

template<typename Spec>
inline size_t execute_core_cycles(
  sgpl::Core<Spec>& state,
  const sgpl::Program<Spec>& program,
  const size_t max_cycles
) {

  using peripheral_t = typename Spec::peripheral_t;
  peripheral_t peripheral;

  return execute_core_cycles<Spec>(state, program, peripheral, max_cycles);

}

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_EXECUTE_CORE_CYCLES_HPP_INCLUDE
