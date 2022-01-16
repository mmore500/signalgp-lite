#pragma once
#ifndef SGPL_ALGORITHM_SLIDE_N_HPP_INCLUDE
#define SGPL_ALGORITHM_SLIDE_N_HPP_INCLUDE

#include <iterator>

#include "slide_to.hpp"

namespace sgpl {

/**
 * Slide a selected window over n positions.
 *
 * Empty space is filled by shifting existing elements outside the window,
 * like dragging and dropping a contiguous selection up or down a list.
 *
 * @param first front of sliding window
 * @param last back of sliding window
 * @param amount how far to slide, left if negative and right if positive
 * @tparam RandomIt random access iterator
 * @return new position of selection window front
 */
template<typename RandomIt>
RandomIt slide_n(RandomIt first, RandomIt last, const int amount) {

  const RandomIt to = (amount > 0)
    ? last + amount
    : first + amount
  ;
  return sgpl::slide_to(first, last, to);

}

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_SLIDE_N_HPP_INCLUDE
