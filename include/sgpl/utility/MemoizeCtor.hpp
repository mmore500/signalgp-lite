#pragma once
#ifndef SGPL_UTILITY_MEMOIZECTOR_HPP_INCLUDE
#define SGPL_UTILITY_MEMOIZECTOR_HPP_INCLUDE

#include "../../../third-party/Empirical/include/emp/datastructs/Cache.hpp"
#include "../../../third-party/Empirical/include/emp/datastructs/tuple_utils.hpp"

namespace sgpl {

template<typename T>
class MemoizeCtor : public T {

  // workaround for inline static thread_local member on g++
  template<typename... Args>
  inline static auto& cache() {
    using cache_t = emp::Cache<
      std::tuple<Args... >,
      T,
      emp::TupleHash<Args... >
    >;
    thread_local cache_t cache{};
    return cache;
  }

public:

  template<typename... Args>
  MemoizeCtor(Args&& ...args) : T(
    lookup(std::forward<Args>(args)...)
  ) { }

  MemoizeCtor(const MemoizeCtor&) = default;

  MemoizeCtor(MemoizeCtor&&) = default;

  template<typename... Args>
  static const T& lookup(Args&& ...args) {
    return cache<Args...>().GetRef(
      std::tuple{ std::forward<Args>(args)... },
      [&](std::tuple<Args...>){ return T( std::forward<Args>(args)... ); }
    );
  }

};

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_MEMOIZECTOR_HPP_INCLUDE
