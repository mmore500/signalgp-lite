#pragma once
#ifndef SGPL_UTILITY_RANDOM_BETWEEN_HPP_INCLUDE
#define SGPL_UTILITY_RANDOM_BETWEEN_HPP_INCLUDE

#include <iterator>

#include "ThreadLocalRandom.hpp"

namespace sgpl {

template<typename InputIt>
InputIt random_between(const InputIt first, const InputIt last){
  const size_t window_width = std::distance(first, last);
  return std::next(
    first,
    sgpl::tlrand.Get().GetUInt(window_width)
  );
}

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_RANDOM_BETWEEN_HPP_INCLUDE
