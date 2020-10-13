#pragma once
#ifndef SGPL_ALGORITHM_MUTATE_BYTES_HPP_INCLUDE
#define SGPL_ALGORITHM_MUTATE_BYTES_HPP_INCLUDE

#include <cstddef>

#include "../../../third-party/Empirical/source/polyfill/span.h"

#include "../utility/ThreadLocalRandom.hpp"

namespace sgpl {

void mutate_bytes(const std::span<std::byte> target) {

  const size_t idx = sgpl::ThreadLocalRandom::Get().GetUInt(
    target.size_bytes()
  );

  target[ idx ] = sgpl::ThreadLocalRandom::GetByte();

}


void mutate_bytes(const std::span<std::byte> target, const size_t num_muts) {

  for (size_t i{}; i < num_muts; ++i) mutate_bytes(target);

}


} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_MUTATE_BYTES_HPP_INCLUDE
