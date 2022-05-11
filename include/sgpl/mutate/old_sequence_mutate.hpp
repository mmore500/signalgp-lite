#pragma once
#ifndef SGPL_MUTATE_OLD_SEQUENCE_MUTATE_COPY_HPP_INCLUDE
#define SGPL_MUTATE_OLD_SEQUENCE_MUTATE_COPY_HPP_INCLUDE

#include <tuple>

#include "../algorithm/sloppy_copy.hpp"
#include "../program/Program.hpp"

namespace sgpl {

template<typename Spec, typename Config>
auto ApplySequenceMutations(
  const sgpl::Program<Spec>& original,
  const Config& cfg
) {

  const bool is_severe = sgpl::tlrand.Get().P(
    cfg.SGPL_SEQMUTATE_INST_INDEL_RATE() // old SGPL_SEVERE_SEQUENCE_MUTATION_RATE
  );

  const size_t defect_bound = (
    is_severe
    ? original.size()
    : cfg.SGPL_MINOR_SEQUENCE_MUTATION_BOUND()
  );

  const double defect_rate
    = cfg.SGPL_SEQUENCE_DEFECT_RATE(); // old SGPL_SEQUENCE_DEFECT_RATE

  size_t num_muts = 0;

  // do severe sequence mutation with scrambling
  auto [copy1, muts1] = sgpl::sloppy_copy<sgpl::Program<Spec>, true>(
    original,
    defect_rate,
    { -defect_bound, defect_bound },
    cfg.SGPL_PROGRAM_SIZE_CAP()
  );

  num_muts += muts1;

  // do severe sequence mutation without scrambling
  auto [copy2, muts2] = sgpl::sloppy_copy<sgpl::Program<Spec>, false>(
    copy1,
    defect_rate,
    { -defect_bound, defect_bound },
    cfg.SGPL_PROGRAM_SIZE_CAP()
  );

  num_muts += muts2;

  return std::make_tuple(copy2, num_muts);
}

}


#endif
