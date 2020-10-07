#pragma once

#include <utility>

#include "../../../third-party/Empirical/source/base/array.h"
#include "../../../third-party/Empirical/source/base/assert.h"

namespace sgpl {

template<typename T, size_t N>
class CappedSet {

  emp::array<T, N> data;

  size_t size_{};

public:

  T& operator[]( const size_t pos ) { return data[pos]; }

  const T& operator[]( const size_t pos ) const { return data[pos]; }

  bool try_push_back( const T& value ) {
    if ( !full() ) {
      push_back( value );
      return true;
    } else return false;
  }

  bool try_push_back( T&& value ) {
    if ( !full() ) {
      push_back( std::move( value ) );
      return true;
    } else return false;
  }

  void push_back( const T& value ) { data[size()] = value; ++size_; }

  void push_back( T&& value ) { data[size()] = std::move( value ); ++size_; }

  void clear() { size_ = 0; }

  size_t size() const { return size_; }

  constexpr size_t max_size() const { return N; }

  bool empty() const { return size(); }

  bool full() const { return size() == N; }

  void pop_back() { emp_assert( size() ); --size_; }

  T& back() { emp_assert( size() ); return operator[](size() - 1); };

  const T& back() const {
   emp_assert( size() );
   return operator[](size() - 1);
 };

  T& front() { return data.front(); };

  const T& front()  const { return data.front(); };

  void erase( const size_t pos ) {
    operator[](pos) = std::move( back() );
    pop_back();
  }

  T* begin() { return &front(); }

  const T* begin() const { return &front(); }

  T* end() { return &back() + 1; }

  const T* end() const { return &back() + 1; }

};

} // namespace sgpl
