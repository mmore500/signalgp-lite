#pragma once
#ifndef SGPL_UTILITY_DO_RANDOM_WALK_EXACT_HPP_INCLUDE
#define SGPL_UTILITY_DO_RANDOM_WALK_EXACT_HPP_INCLUDE

#include <cmath>

#include "../debug/sgpl_assert.hpp"

#include "random_sign.hpp"

namespace sgpl {

// random walk with n steps on a one dimensional lattice
int do_random_walk_exact(const int num_steps) {

  sgpl_assert( num_steps >= 0, num_steps );

  int res{};
  for (int i{}; i < num_steps; ++i) res += sgpl::random_sign();

  return res;

}

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_DO_RANDOM_WALK_EXACT_HPP_INCLUDE
