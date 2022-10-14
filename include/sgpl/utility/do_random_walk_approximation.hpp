#pragma once
#ifndef SGPL_UTILITY_DO_RANDOM_WALK_APPROXIMATION_HPP_INCLUDE
#define SGPL_UTILITY_DO_RANDOM_WALK_APPROXIMATION_HPP_INCLUDE

#include "../debug/sgpl_assert.hpp"

#include "do_random_walk_indexmap_approximation.hpp"
#include "do_random_walk_normal_approximation.hpp"

namespace sgpl {

// random walk with n steps on a one dimensional lattice
int do_random_walk_approximation(const int num_steps) {
  sgpl_assert( num_steps >= 0, num_steps );

  if ( num_steps == 0 ) return 0;
  else if (num_steps < 10) {
    return sgpl::do_random_walk_indexmap_approximation(num_steps);
  } else return sgpl::do_random_walk_normal_approximation(num_steps);

}

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_DO_RANDOM_WALK_APPROXIMATION_HPP_INCLUDE
