#pragma once
#ifndef SGPL_UTILITY_THREADLOCALRANDOM_HPP_INCLUDE
#define SGPL_UTILITY_THREADLOCALRANDOM_HPP_INCLUDE

#include <cstddef>

#include "../../../third-party/Empirical/include/emp/base/assert.hpp"
#include "../../../third-party/Empirical/include/emp/math/Random.hpp"

namespace sgpl {

class ThreadLocalRandom {

  inline static thread_local emp::Random rand{ 1 };

  inline static uint32_t cache{ rand.GetUInt() };

  inline static std::byte* cache_ptr{reinterpret_cast<std::byte*>( &cache )};

  inline static size_t cache_pos{};

public:

  static emp::Random& Get() { return rand; }

  static std::byte GetByte() {
    const auto res { cache_ptr[cache_pos] };
    ++cache_pos;
    if ( cache_pos == sizeof( cache ) ) {
      cache_pos %= sizeof( cache );
      cache = rand.GetUInt();
    }
    return res;
  }

  static void Reseed( const int seed ) {

    // seed <= 0 non-deterministic (uses system time and memory address)
    emp_assert( seed > 0 );

    rand = emp::Random{ seed };

  }

  static void Initialize( const int seed ) {

    // assert that rng hasn't been touched already
    emp_assert( rand.GetUInt() == emp::Random{ 1 }.GetUInt() );

    Reseed( seed );

  }

  static void SeedStochastically() { rand = emp::Random{ -1 }; }

};


} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_THREADLOCALRANDOM_HPP_INCLUDE
