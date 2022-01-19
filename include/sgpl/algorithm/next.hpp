#pragma once
#ifndef SGPL_ALGORITHM_NEXT_HPP_INCLUDE
#define SGPL_ALGORITHM_NEXT_HPP_INCLUDE

#include <iterator>

namespace sgpl {

// see http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4317.pdf
template<typename InputIt>
InputIt next(
  InputIt it,
  InputIt bound,
  typename std::iterator_traits<InputIt>::difference_type n=1
) {
  return std::next(
    it,
    std::min(
      std::distance( it, bound ),
      n
    )
  );
}

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_NEXT_HPP_INCLUDE
