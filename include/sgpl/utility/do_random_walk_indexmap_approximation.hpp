#pragma once
#ifndef SGPL_UTILITY_DO_RANDOM_WALK_INDEXMAP_APPROXIMATION_HPP_INCLUDE
#define SGPL_UTILITY_DO_RANDOM_WALK_INDEXMAP_APPROXIMATION_HPP_INCLUDE

#include "../../../third-party/conduit/include/uitsl/algorithm/clamp_cast.hpp"
#include "../../../third-party/conduit/include/uit_emp/math/Distribution.hpp"

#include "../debug/sgpl_assert.hpp"

#include "MemoizeCtor.hpp"
#include "ThreadLocalRandom.hpp"

namespace sgpl {

int do_random_walk_indexmap_approximation(const int num_steps) {
  sgpl_assert( num_steps >= 0, num_steps );
  const auto& distn = sgpl::MemoizeCtor<uit_emp::Binomial>::lookup(
    0.5, num_steps
  );
  return 2 * distn.PickRandom( sgpl::tlrand.Get() ) - num_steps;
}

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_DO_RANDOM_WALK_INDEXMAP_APPROXIMATION_HPP_INCLUDE
