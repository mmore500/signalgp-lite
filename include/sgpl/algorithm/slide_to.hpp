#pragma once
#ifndef SGPL_ALGORITHM_SLIDE_TO_HPP_INCLUDE
#define SGPL_ALGORITHM_SLIDE_TO_HPP_INCLUDE

#include <algorithm>
#include <cassert>

namespace sgpl {

/**
 * Move the a selected range to a target position.
 *
 * The front of the selected range is repositioned so as if inserted before the
 * target position. If the target position is within the selected range this
 * will result in a no-op. In the case of an empty selected range, the target
 * position is returned.
 *
 * @param first front of selection
 * @param last back of selection
 * @param to target to slide to
 * @tparam random access iterator type
 * @return iterator at the new position of the front of the selected range
 */
template<typename RandomIt>
RandomIt slide_to(const RandomIt first, const RandomIt last, const RandomIt to) {

  assert( first <= last );

  // adapted from https://youtu.be/W2tWOdzgXHA?t=778
  // slide backward
  if (to < first) {
    std::rotate(to, first, last);
    return to;
  }
  // slide forward
  else if (last < to) return std::rotate(first, last, to);
  // slide inside selected window
  else return first;

}

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_SLIDE_TO_HPP_INCLUDE
