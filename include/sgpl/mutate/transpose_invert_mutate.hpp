#pragma once
#ifndef SGPL_MUTATE_TRANSPOSE_INVERT_MUTATE_HPP_INCLUDE
#define SGPL_MUTATE_TRANSPOSE_INVERT_MUTATE_HPP_INCLUDE

#include <algorithm>
#include <iterator>

#include "../algorithm/transpose_window.hpp"
#include "../program/Program.hpp"
#include "../utility/MemoizeCtor.hpp"
#include "../utility/random_between.hpp"
#include "../utility/ThreadLocalRandom.hpp"

namespace sgpl {

template<typename Config, typename Spec>
size_t transpose_invert_mutate(
  sgpl::Program<Spec> & program,
  const Config& cfg
) {

  // ideally, we would draw from the binomial distn,
  // but that's expensive with varying n...
  // so approximate with the poisson distribution instead
  // they're similar-ish, e.g., https://www.researchgate.net/figure/Poisson-versus-binomial-distribution-from-number-of-heads-in-a-coin-toss-The-Poisson_fig3_255717571
  // (they become more similar for large n)
  const size_t num_transpositions = sgpl::tlrand.Get().GetRandPoisson(
    program.size(),
    cfg.SGPL_SEQMUTATE_INST_TRANSPOSE_RATE()
  );
  const sgpl::TransposeWindowDisplacementGenerator_Default disp_gen(cfg);
  const sgpl::TransposeWindowSizeGenerator_Default size_gen(cfg);

  size_t num_rearranged_sites{};
  for (size_t i{}; i < num_transpositions; ++i) {
    const auto [
      transposedfrom_window_first,
      transposedto_window_first,
      transposedto_window_last
    ] = sgpl::transpose_window(
      std::begin(program),
      std::end(program),
      disp_gen,
      size_gen
    );

    const auto displacement = std::abs(
      std::distance(transposedfrom_window_first, transposedto_window_first)
    );
    const auto window_size = std::distance(
      transposedto_window_first, transposedto_window_last
    );

    num_rearranged_sites += std::min(displacement, window_size);

    if (sgpl::tlrand.Get().P(
      cfg.SGPL_SEQMUTATE_INST_TRANSPOSE_INVERSION_RATE()
    )) {
      std::reverse(transposedto_window_first, transposedto_window_first);
      num_rearranged_sites += window_size;
    }
  }

  return num_rearranged_sites;
}

} // namespace sgpl

#endif // #ifndef SGPL_MUTATE_TRANSPOSE_INVERT_MUTATE_HPP_INCLUDE
