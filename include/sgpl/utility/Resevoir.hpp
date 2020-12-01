#pragma once
#ifndef SGPL_UTILITY_RESEVOIR_HPP_INCLUDE
#define SGPL_UTILITY_RESEVOIR_HPP_INCLUDE

#include <utility>

#include "../../../third-party/Empirical/include/emp/base/array.hpp"
#include "../../../third-party/Empirical/include/emp/base/assert.hpp"

namespace sgpl {

template<typename T, size_t N>
class Resevoir {

  emp::array<T, N> buffer;

  size_t size_{};

public:

  T& operator[]( const size_t pos ) { return buffer[pos]; }

  const T& operator[]( const size_t pos ) const { return buffer[pos]; }

  bool try_acquire() {
    if ( !full() ) {
      acquire();
      return true;
    } else return false;
  }

  void acquire() { ++size_; }

  void clear() { size_ = 0; }

  size_t size() const { return size_; }

  constexpr size_t max_size() const { return N; }

  bool empty() const { return size(); }

  bool full() const { return size() == N; }

  void release_back() { --size_; }

  T& back() { emp_assert( size() ); return operator[](size() - 1); };

  const T& back() const {
   emp_assert( size() );
   return operator[](size() - 1);
 };

  T& front() { return buffer.front(); };

  const T& front()  const { return buffer.front(); };

  void release( const size_t pos ) {
    std::swap( operator[](pos), back() );
    release_back();
  }

  T* begin() { return &front(); }

  const T* begin() const { return &front(); }

  T* end() { return begin() + size(); }

  const T* end() const { return begin() + size(); }

  auto& buffer() { return buffer; }

  const auto& buffer() const { return buffer; }

};

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_RESEVOIR_HPP_INCLUDE
