#pragma once
#ifndef SGPL_MORPH_NOP_OUT_NTH_OP_HPP_INCLUDE
#define SGPL_MORPH_NOP_OUT_NTH_OP_HPP_INCLUDE

#include <cassert>

#include "../debug/sgpl_always_assert.hpp"
#include "../introspection/count_op_instructions.hpp"
#include "../program/Program.hpp"

namespace sgpl {

template< typename Spec >
sgpl::Program<Spec> nop_out_nth_op(
  sgpl::Program<Spec> program,
  const size_t n
) {

  assert( n < sgpl::count_op_instructions<Spec>( program ) );

  size_t op_counter{};
  for ( size_t idx{}; idx < program.size(); ++idx ) {
    auto& inst = program[ idx ];

    if ( op_counter == n && inst.IsOp() ) {
      inst.NopOut();
      return program;
    } else op_counter += inst.IsOp();

  }

  sgpl_always_assert( false, n << program.size() );
  __builtin_unreachable();

}

} // namespace sgpl

#endif // #ifndef SGPL_MORPH_NOP_OUT_NTH_OP_HPP_INCLUDE
