#pragma once
#ifndef SGPL_ALGORITHM_EXECUTE_CORE_HPP_INCLUDE
#define SGPL_ALGORITHM_EXECUTE_CORE_HPP_INCLUDE

#include <algorithm>

#include "../../../third-party/Empirical/include/emp/base/assert.hpp"
#include "../../../third-party/Empirical/include/emp/base/macros.hpp"

#include "../hardware/Core.hpp"
#include "../program/Instruction.hpp"
#include "../program/Program.hpp"

#include "advance_core.hpp"

namespace sgpl {

template<typename Spec>
size_t execute_core(
  sgpl::Core<Spec>& state,
  const sgpl::Program<Spec>& program,
  typename Spec::peripheral_t& peripheral,
  size_t max_cycles
) {

  /**
   * We need to make sure that the GlobalJumpTable is populated
   * /except/ when the program has no modules.
   * In this case, when there are no GlobalAnchors within the program,
   * it is acceptable for the GlobalJumpTable to be empty.
   */
  emp_assert(
    state.GetGlobalJumpTable().GetSize()
    || !program.HasGlobalAnchor(),
    "Global anchors not initialized! "
    "Hint: call Cpu.InitializeAnchors()",
    state.GetGlobalJumpTable().GetSize(),
    program.HasGlobalAnchor()
  );
  max_cycles = std::min(Spec::switch_steps, max_cycles);

  size_t i;
  for (i = 0; i < max_cycles && !state.HasTerminated(); ++i) {
    advance_core<Spec>(state, program, peripheral);
  }
  return i;

};

template<typename Spec>
inline size_t execute_core(
  sgpl::Core<Spec>& state,
  const sgpl::Program<Spec>& program,
  typename Spec::peripheral_t& peripheral
) {

  return execute_core(state, program, peripheral, Spec::switch_steps);

};

template<typename Spec>
inline size_t execute_core(
  sgpl::Core<Spec>& state,
  const sgpl::Program<Spec>& program
) {

  using peripheral_t = typename Spec::peripheral_t;
  peripheral_t peripheral;

  return execute_core<Spec>(state, program, peripheral);

}


} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_EXECUTE_CORE_HPP_INCLUDE
