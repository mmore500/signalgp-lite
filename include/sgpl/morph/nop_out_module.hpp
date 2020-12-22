#pragma once
#ifndef SGPL_MORPH_NOP_OUT_MODULE_HPP_INCLUDE
#define SGPL_MORPH_NOP_OUT_MODULE_HPP_INCLUDE

#include <iterator>

#include "../../../third-party/Empirical/include/emp/base/vector.hpp"

#include "../program/GlobalAnchorIterator.hpp"
#include "../program/Program.hpp"

#include "nop_out_instructions.hpp"

namespace sgpl {

template< typename Spec >
sgpl::Program<Spec> nop_out_module(
  sgpl::Program<Spec> program, const size_t module_idx
) {

  const auto& inst_begin = *std::next(
    sgpl::GlobalAnchorIterator<Spec>::make_begin(program),
    module_idx
  );

  const auto& inst_end = *std::next(
    sgpl::GlobalAnchorIterator<Spec>::make_begin(program),
    module_idx + 1
  );

  emp::vector< char > should_nop;
  for (int idx{}; static_cast<size_t>(idx) < program.size(); ++idx) {
    const auto& as_const = program;
    should_nop.push_back(
      idx >= std::distance( &as_const.front(), &inst_begin )
      && idx < std::distance( &as_const.front(), &inst_end )
    );
  }

  return sgpl::nop_out_instructions<Spec>( program, should_nop );

}

} // namespace sgpl

#endif // #ifndef SGPL_MORPH_NOP_OUT_MODULE_HPP_INCLUDE
