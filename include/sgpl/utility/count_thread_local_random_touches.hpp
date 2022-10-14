#pragma once
#ifndef SGPL_UTILITY_COUNT_THREAD_LOCAL_RANDOM_TOUCHES_HPP_INCLUDE
#define SGPL_UTILITY_COUNT_THREAD_LOCAL_RANDOM_TOUCHES_HPP_INCLUDE

#include <algorithm>
#include <cstddef>
#include <functional>

#include "../../../third-party/conduit/include/uit_emp/math/Random.hpp"
#include "../../../third-party/conduit/include/uit_emp/math/random_utils.hpp"

#include "ThreadLocalRandom.hpp"

namespace sgpl {

size_t count_thread_local_random_touches(const std::function<void()> routine) {

  return uit_emp::CountRngTouches( [routine]( uit_emp::Random& rand ){
    std::swap( sgpl::tlrand.Get(), rand );
    routine();
    std::swap( sgpl::tlrand.Get(), rand );
  } );

}

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_COUNT_THREAD_LOCAL_RANDOM_TOUCHES_HPP_INCLUDE
