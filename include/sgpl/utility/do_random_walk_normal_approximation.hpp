#pragma once
#ifndef SGPL_UTILITY_DO_RANDOM_WALK_NORMAL_APPROXIMATION_HPP_INCLUDE
#define SGPL_UTILITY_DO_RANDOM_WALK_NORMAL_APPROXIMATION_HPP_INCLUDE

#include <cmath>

#include "../../../third-party/conduit/include/uitsl/algorithm/clamp_cast.hpp"

#include "../debug/sgpl_assert.hpp"

#include "ThreadLocalRandom.hpp"

namespace sgpl {

// uses normal approximation to the binomial
// good approximation for n > 9
// https://en.wikipedia.org/wiki/Binomial_distribution#Normal_approximation
int do_random_walk_normal_approximation(const int num_steps) {
  sgpl_assert( num_steps >= 0, num_steps );
  return std::clamp(
    /*
     * Binomial(n, p) ~= Normal(np, sqrt(np(1-p)))
     * so...
     * Binomial(n, 0.5) ~= Normal(n/2, sqrt(n/4))
     * so...
     * 2 * Binomial(n, 0.5) - n ~= 2 * Normal(n/2, sqrt(n/4)) - n
     * 2 * Binomial(n, 0.5) - n ~= 2 * Normal(0, sqrt(n/4))
     * 2 * Binomial(n, 0.5) - n ~= 2 * Normal(0, sqrt(n)/2)
     * 2 * Binomial(n, 0.5) - n ~= Normal(0, sqrt(n))
     */
    uitsl::clamp_cast<int>( std::round(
      sgpl::tlrand.Get().GetRandNormal(0, std::sqrt(num_steps))
    ) ),
    -num_steps, num_steps
  );
}

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_DO_RANDOM_WALK_NORMAL_APPROXIMATION_HPP_INCLUDE
