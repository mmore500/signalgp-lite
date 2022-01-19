#pragma once
#ifndef SGPL_MUTATE_SEQUENCE_MUTATE_COPY_HPP_INCLUDE
#define SGPL_MUTATE_SEQUENCE_MUTATE_COPY_HPP_INCLUDE

#include <tuple>

#include "../algorithm/module_indel_copy.hpp"
#include "../program/GlobalAnchorIterator.hpp"
#include "../program/Program.hpp"
#include "../utility/CappedOutputIterator.hpp"

#include "../spec/InstRangeCopier_Indel.hpp"

namespace sgpl {

template<
  typename Spec,
  typename InstRangeCopier=sgpl::InstRangeCopier_Indel
>
auto sequence_mutate_copy(
  const sgpl::Program<Spec>& original,
  const float p_module_defect,
  const float p_module_defect_is_insertion,
  const size_t program_size_cap,
  const InstRangeCopier& range_copier={}
) {

  std::tuple<sgpl::Program<Spec>, size_t> res;
  auto& program_copy = std::get<sgpl::Program<Spec>>(res);
  auto& num_muts = std::get<size_t>(res);

  program_copy.reserve(original.size());

  using anchorit_t = sgpl::GlobalAnchorIterator<Spec>;
  num_muts = module_indel_copy(
    anchorit_t::make_begin(original), anchorit_t::make_end(original),
    sgpl::CappedOutputIterator(
      std::back_inserter( program_copy ),
      program_size_cap
    ),
    p_module_defect,
    p_module_defect_is_insertion,
    range_copier
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
    cfg.SGPL_PROGRAM_SIZE_CAP(),
    sgpl::InstRangeCopier_Indel(cfg)
  );

}

} // namespace sgpl

#endif // #ifndef SGPL_MUTATE_SEQUENCE_MUTATE_COPY_HPP_INCLUDE
