#pragma once

#include <numeric>
#include <utility>

#include "../../../third-party/conduit/include/uitsl/datastructs/RingBuffer.hpp"
#include "../../../third-party/conduit/include/uitsl/debug/safe_compare.hpp"
#include "../../../third-party/Empirical/source/base/array.h"
#include "../../../third-party/Empirical/source/base/assert.h"
#include "../../../third-party/Empirical/source/base/optional.h"

namespace sgpl {

template<typename T, size_t N>
class RingResevoir {

  emp::array<T, N> buffer{};

  size_t tail_index{};
  size_t num_items{};

  inline void AdvanceTail() { ++tail_index %= GetCapacity(); }

  inline size_t GetBufferIndex( const size_t pos ) {
    emp_assert( pos < GetSize() );
    emp_assert( tail_index < GetCapacity() );
    return ( tail_index + pos ) % GetCapacity();
  }

public:

  template<typename It>
  RingResevoir(const It begin, const It end) {
    emp_assert( std::distance(begin, end) >= 0 );
    emp_assert( uitsl::safe_equal(
      std::distance(begin, end), this->GetCapacity()
    ) );
    std::iota( std::begin( buffer ), std::end( buffer ), begin );
  }

  inline size_t GetSize() const { return num_items; }

  constexpr size_t GetCapacity() const { return N; }

  inline size_t GetAvailableCapacity() const {
    return GetCapacity() - GetSize();
  }

  inline bool IsEmpty() const { return GetSize() == 0; }

  inline bool IsFull() const { return GetSize() == GetCapacity(); }

  inline T& GetTail() {
    emp_assert( !IsEmpty() );
    return buffer[tail_index];
  }

  inline T& GetHead() {
    emp_assert( !IsEmpty() );
    return buffer[ GetBufferIndex( GetSize() - 1 ) ];
  }

  T& Acquire() {
    emp_assert( !IsFull() );
    ++num_items;
    return GetHead();
  }

  inline void ReleaseHead() {
    emp_assert( !IsEmpty() );
    --num_items;
  }

  inline void ReleaseTail() {
    emp_assert( !IsEmpty() );
    AdvanceTail();
    --num_items;
  }

  inline bool IsTail(const size_t pos) const { return pos == 0; }

  inline bool IsHead(const size_t pos) const { return pos == GetSize(); }

  void Release( const size_t pos ) {
    if ( IsTail( pos ) ) ReleaseTail();
    else {
      if ( !IsHead( pos ) ) std::swap( this->Get(pos), this->GetHead() );
      ReleaseHead();
    }
  }

  inline T& Get( const size_t pos ) { return buffer[ GetBufferIndex( pos ) ]; }

  inline auto& Deref( const size_t pos ) { return * this->Get( pos ); }

  inline const auto& Deref( const size_t pos ) const {
    return * this->Get( pos );
  }

  inline auto& DerefHead() { return * this->GetHead(); }

  inline const auto& DerefHead() const { return * this->GetHead(); }

  inline auto& DerefTail() { return * this->GetTail(); }

  inline const auto& DerefTail() const { return * this->GetTail(); }

};

} // namespace sgpl
