#pragma once
#ifndef SGPL_ALGORITHM_DRAG_TO_HPP_INCLUDE
#define SGPL_ALGORITHM_DRAG_TO_HPP_INCLUDE

#include <algorithm>
#include <cassert>
#include <iterator>

namespace sgpl {

/**
 * Move the front of a selected range to a target position.
 *
 * The front of the selected range is repositioned so as if inserted before the
 * target position. If the target position is within the selected range,
 * performs a rotate so that the front of the selection reaches the target
 * position. Note that for target position equal or one after the front of the
 * selected range, this will result in a no-op. In the case of an empty
 * selected range, the target position is returned.
 *
 * @param first front of selection
 * @param last back of selection
 * @param to target to slide to
 * @tparam random access iterator type
 * @return iterator at the new position of the front of the selected range
 */
template<typename RandomIt>
RandomIt drag_to(const RandomIt first, const RandomIt last, const RandomIt to) {

  assert( first <= last );

  // adapted from https://youtu.be/W2tWOdzgXHA?t=778
  // slide backward
  if (to < first) {
    std::rotate(to, first, last);
    return to;
  }
  // slide forward
  else if (last < to) return std::rotate(first, last, to);
  else if (first == to) return first;
  // rotate (slide target is inside selection)
  else return std::rotate(
    first,
    std::next(first, std::distance(to, last) + 1),
    last
  );

}

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_DRAG_TO_HPP_INCLUDE
