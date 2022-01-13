#pragma once
#ifndef SGPL_MUTATE_SEQUENCE_MUTATE_COPY_HPP_INCLUDE
#define SGPL_MUTATE_SEQUENCE_MUTATE_COPY_HPP_INCLUDE

#include <tuple>

#include "../algorithm/inst_indel_copy.hpp"
#include "../algorithm/module_indel_copy.hpp"
#include "../program/GlobalAnchorIterator.hpp"
#include "../program/Program.hpp"

namespace sgpl {

struct IndelRangeCopier {

  float p_defect;
  float p_defect_is_insertion;
  float p_garble;

  IndelRangeCopier(
    const float p_defect_,
    const float p_defect_is_insertion_=0.5f,
    const float p_garble_=0.f
  ) : p_defect(p_defect_)
  , p_defect_is_insertion(p_defect_is_insertion_)
  , p_garble(p_garble_)
  { }

  template<typename Config>
  explicit IndelRangeCopier(const Config& cfg)
  : p_defect(cfg.SGPL_SEQMUTATE_INST_INDEL_RATE())
  , p_defect_is_insertion(cfg.SGPL_SEQMUTATE_INST_INDEL_FRAC_INSERTIONS())
  , p_garble(cfg.SGPL_SEQMUTATE_INST_INDEL_GARBLE_RATE())
  { }

  // return additional indels
  template<typename InputIt, typename OutputIt>
  size_t copy(InputIt first, InputIt last, OutputIt out) const {
    return sgpl::inst_indel_copy(first, last, out, p_defect, p_garble);
  }

  IndelRangeCopier& SetPDefect(const float v) { p_defect = v; return *this; }
  IndelRangeCopier& SetPDefectIsInsertion(const float v) {
    p_defect_is_insertion = v; return *this;
  }
  IndelRangeCopier& SetPGarble(const float v) { p_garble = v; return *this; }

  IndelRangeCopier& KnockoutInsertionMutations() {
    // only deletion mutations remain
    p_defect *= (1.f - p_defect_is_insertion);
    p_defect_is_insertion = 0.f;
    return *this;
  }
  IndelRangeCopier& KnockoutDeletionMutations() {
    // only insertion mutations remain
    p_defect *= p_defect_is_insertion;
    p_defect_is_insertion = 1.f;
    return *this;
  }

};

template<typename Spec>
auto sequence_mutate_copy(
  const sgpl::Program<Spec>& original,
  const float p_module_defect,
  const float p_module_defect_is_insertion,
  const sgpl::IndelRangeCopier& copier
) {

  std::tuple<sgpl::Program<Spec>, size_t> res;
  auto& program_copy = std::get<sgpl::Program<Spec>>(res);
  auto& num_muts = std::get<size_t>(res);

  program_copy.reserve(original.size());

  using anchorit_t = sgpl::GlobalAnchorIterator<Spec>;
  num_muts = module_indel_copy(
    anchorit_t::make_begin(original), anchorit_t::make_end(original),
    std::back_inserter( program_copy ),
    p_module_defect,
    p_module_defect_is_insertion,
    copier
  );

  return res;

}

template<typename Spec, typename Config>
auto sequence_mutate_copy(
  const sgpl::Program<Spec>& original,
  const Config& cfg
) {

  return sequence_mutate_copy<Spec>(
    original,
    cfg.SGPL_SEQMUTATE_MODULE_INDEL_RATE(),
    cfg.SGPL_SEQMUTATE_MODULE_INDEL_FRAC_INSERTIONS(),
    sgpl::IndelRangeCopier(cfg)
  );

}

} // namespace sgpl

#endif // #ifndef SGPL_MUTATE_SEQUENCE_MUTATE_COPY_HPP_INCLUDE
