#pragma once
#ifndef SGPL_MUTATE_MUTATE_COPY_HPP_INCLUDE
#define SGPL_MUTATE_MUTATE_COPY_HPP_INCLUDE

#include <tuple>

#include "../program/Program.hpp"

#include "point_mutate.hpp"
#include "sequence_mutate_copy.hpp"
#include "transpose_invert_mutate.hpp"

namespace sgpl {

template<typename Spec, typename Config>
auto mutate_copy(
  const sgpl::Program<Spec>& original,
  const Config& cfg
) {

  auto res = sgpl::sequence_mutate_copy(original, cfg);
  auto& [program_copy, num_muts] = res;

  num_muts += sgpl::point_mutate(program_copy, cfg);

  num_muts += sgpl::transpose_invert_mutate(program_copy, cfg);

  return res;

}

} // namespace sgpl

#endif // #ifndef SGPL_MUTATE_MUTATE_COPY_HPP_INCLUDE
