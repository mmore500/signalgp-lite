#pragma once
#ifndef SGPL_MORPH_NOP_OUT_MODULES_HPP_INCLUDE
#define SGPL_MORPH_NOP_OUT_MODULES_HPP_INCLUDE

#include "../../../third-party/Empirical/include/emp/base/vector.hpp"

#include "../introspection/count_modules.hpp"
#include "../program/Program.hpp"

#include "nop_out_module.hpp"

namespace sgpl {

template< typename Spec >
sgpl::Program<Spec> nop_out_modules(
  sgpl::Program<Spec> program, emp::vector<char> should_nop
) {

  emp_assert( sgpl::count_modules<Spec>( program ) == should_nop.size() );

  for (size_t module_idx{}; module_idx < should_nop.size(); ++module_idx) {
    if ( should_nop[ module_idx ] ) {
      program = sgpl::nop_out_module( program, module_idx );
    }
  }

  return program;

}

} // namespace sgpl

#endif // #ifndef SGPL_MORPH_NOP_OUT_MODULES_HPP_INCLUDE
