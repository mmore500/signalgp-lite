#pragma once
#ifndef SGPL_UTILITY_COUNT_THREAD_LOCAL_RANDOM_TOUCHES_HPP_INCLUDE
#define SGPL_UTILITY_COUNT_THREAD_LOCAL_RANDOM_TOUCHES_HPP_INCLUDE

#include <algorithm>
#include <cstddef>
#include <functional>

#include "../../../third-party/Empirical/source/tools/Random.h"
#include "../../../third-party/Empirical/source/tools/random_utils.h"

#include "ThreadLocalRandom.hpp"

namespace sgpl {

size_t count_thread_local_random_touches(const std::function<void()> routine) {

  return emp::CountRngTouches( [routine]( emp::Random& rand ){
    std::swap( sgpl::ThreadLocalRandom::Get(), rand );
    routine();
    std::swap( sgpl::ThreadLocalRandom::Get(), rand );
  } );

}

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_COUNT_THREAD_LOCAL_RANDOM_TOUCHES_HPP_INCLUDE
