#pragma once
#ifndef SGPL_MUTATE_POINT_MUTATE_HPP_INCLUDE
#define SGPL_MUTATE_POINT_MUTATE_HPP_INCLUDE

#include "../program/Program.hpp"

namespace sgpl {

template<typename Config, typename Spec>
size_t point_mutate(
  sgpl::Program<Spec> & program,
  const Config& cfg
) {
  return program.ApplyPointMutations(
    cfg.SGPL_POINTMUTATE_BITFLIP_RATE()
  );
}

} // namespace sgpl

#endif // #ifndef SGPL_MUTATE_POINT_MUTATE_HPP_INCLUDE
