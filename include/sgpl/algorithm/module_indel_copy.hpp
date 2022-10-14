#pragma once
#ifndef SGPL_ALGORITHM_MODULE_INDEL_COPY_HPP_INCLUDE
#define SGPL_ALGORITHM_MODULE_INDEL_COPY_HPP_INCLUDE

#include <cmath>
#include <limits>
#include <tuple>
#include <utility>

#include "../program/GlobalAnchorIterator.hpp"
#include "../program/Program.hpp"
#include "../spec/InstRangeCopier_Default.hpp"
#include "../utility/random_sign.hpp"
#include "../utility/ThreadLocalRandom.hpp"

namespace sgpl {

/*
 * @note if output program length should be limited,
 * use sgpl::CappedOutputIterator
 */
template <
  typename ModuleIt,
  typename OutputIt,
  typename InstRangeCopier=sgpl::InstRangeCopier_Default
>
size_t module_indel_copy(
  ModuleIt program_begin, ModuleIt program_end,
  OutputIt out_iter,
  const float p_defect, const float p_defect_is_insertion=0.5f,
  const InstRangeCopier& range_copier=InstRangeCopier()
) {

  size_t cumulative_insertion_deletion{};

  // aft (front) and stern (back) like on a boat
  auto stern_it = program_begin;
  auto aft_it = program_begin;
  if (program_begin != program_end) do {

    stern_it = std::exchange( aft_it, std::next(aft_it) );

    const auto cur_module_begin = stern_it.begin();
    const auto cur_module_end = aft_it.begin();
    const size_t cur_module_length = std::distance(
      cur_module_begin,
      cur_module_end
    );

    // draw number of module copies to copy into result
    const bool do_indel = sgpl::tlrand.Get().P( p_defect );
    const size_t num_module_copies = (
      1 + do_indel * sgpl::random_sign( p_defect_is_insertion )
    );

    if (do_indel) cumulative_insertion_deletion += cur_module_length;

    // copy module into result n times
    for (size_t i{}; i < num_module_copies; ++i) {
      cumulative_insertion_deletion += range_copier(
        cur_module_begin, cur_module_end,
        out_iter
      );
    }

  } while ( aft_it != program_end );

  return cumulative_insertion_deletion;

}

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_MODULE_INDEL_COPY_HPP_INCLUDE
