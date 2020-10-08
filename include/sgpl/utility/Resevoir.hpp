#pragma once

#include <utility>

#include "../../../third-party/Empirical/source/base/array.h"
#include "../../../third-party/Empirical/source/base/assert.h"

namespace sgpl {

template<typename T, size_t N>
class Resevoir {

  emp::array<T, N> data_;

  size_t size_{};

public:

  T& operator[]( const size_t pos ) { return data_[pos]; }

  const T& operator[]( const size_t pos ) const { return data_[pos]; }

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

  T& front() { return data_.front(); };

  const T& front()  const { return data_.front(); };

  void release( const size_t pos ) {
    std::swap( operator[](pos), back() );
    release_back();
  }

  T* begin() { return &front(); }

  const T* begin() const { return &front(); }

  T* end() { return begin() + size(); }

  const T* end() const { return begin() + size(); }

  emp::array<T, N>& array() { return data_; }

  const emp::array<T, N>& array() const { return data_; }

};

} // namespace sgpl
