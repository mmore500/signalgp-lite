#pragma once
#ifndef SGPL_ALGORITHM_INST_INDEL_COPY_HPP_INCLUDE
#define SGPL_ALGORITHM_INST_INDEL_COPY_HPP_INCLUDE

#include <limits>
#include <tuple>
#include <utility>
#include <vector>

#include "../../../third-party/conduit/include/uitsl/debug/audit_cast.hpp"

#include "../utility/do_random_walk_normal_approximation.hpp"
#include "../utility/GarbledOutputIterator.hpp"
#include "../utility/random_sign.hpp"
#include "../utility/ThreadLocalRandom.hpp"

namespace sgpl {

/*
 * @note if output program length should be limited,
 * use sgpl::CappedOutputIterator
 */
template<typename InputIt, typename OutputIt>
size_t inst_indel_copy(
  InputIt first, InputIt last,
  OutputIt out_iter,
  const float p_defect,
  const float p_garble=0.f,
  const float p_defect_is_insertion=0.5f
) {

  size_t cumulative_insertion_deletion{};

  auto garbled_out_iter = sgpl::GarbledOutputIterator( out_iter );

  const int len = std::distance(first, last);
  for (auto cur = first; cur != last; ++cur) {
    if (sgpl::tlrand.Get().P(p_defect)) {
      // draw as random walk 4x available space
      // tuning for 4*len walk: https://www.desmos.com/calculator/b1feurshxg
      const int raw_defect = (
        -1 * std::abs(sgpl::do_random_walk_normal_approximation(4*len))
        * sgpl::random_sign(p_defect_is_insertion)
      );
      // clamp to valid range
      const int defect = std::clamp(
        raw_defect,
        uitsl::audit_cast<int>( std::distance(cur, first) ),
        uitsl::audit_cast<int>( std::distance(cur, last) - 1 )
      );
      std::advance(cur, defect);
      cumulative_insertion_deletion += std::abs( defect );
      if ( sgpl::tlrand.Get().P(p_garble) ) {
        garbled_out_iter.AddGarble( -defect );
      }
    }
    *garbled_out_iter++ = *cur;
  }

  return cumulative_insertion_deletion;

}


} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_INST_INDEL_COPY_HPP_INCLUDE
