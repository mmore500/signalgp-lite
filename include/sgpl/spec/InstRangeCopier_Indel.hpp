#pragma once
#ifndef SGPL_SPEC_INSTRANGECOPIER_INDEL_HPP_INCLUDE
#define SGPL_SPEC_INSTRANGECOPIER_INDEL_HPP_INCLUDE

#include "../algorithm/inst_indel_copy.hpp"

#include "StarterConfig.hpp"

namespace sgpl {

struct InstRangeCopier_Indel {

  float p_defect;
  float p_defect_is_insertion;
  float p_garble;

  InstRangeCopier_Indel(
    const float p_defect_,
    const float p_defect_is_insertion_=0.5f,
    const float p_garble_=0.f
  ) : p_defect(p_defect_)
  , p_defect_is_insertion(p_defect_is_insertion_)
  , p_garble(p_garble_)
  { }

  template<typename Config=sgpl::StarterConfig>
  explicit InstRangeCopier_Indel(const Config& cfg={})
  : p_defect(cfg.SGPL_SEQMUTATE_INST_INDEL_RATE())
  , p_defect_is_insertion(cfg.SGPL_SEQMUTATE_INST_INDEL_FRAC_INSERTIONS())
  , p_garble(cfg.SGPL_SEQMUTATE_INST_INDEL_GARBLE_RATE())
  { }

  // return additional indels
  template<typename InputIt, typename OutputIt>
  size_t operator()(InputIt first, InputIt last, OutputIt out) const {
    return sgpl::inst_indel_copy(first, last, out, p_defect, p_garble);
  }

  InstRangeCopier_Indel& SetPDefect(const float v) {
    p_defect = v; return *this;
  }
  InstRangeCopier_Indel& SetPDefectIsInsertion(const float v) {
    p_defect_is_insertion = v; return *this;
  }
  InstRangeCopier_Indel& SetPGarble(const float v) {
    p_garble = v; return *this;
  }

  InstRangeCopier_Indel& KnockoutInsertionMutations() {
    // only deletion mutations remain
    p_defect *= (1.f - p_defect_is_insertion);
    p_defect_is_insertion = 0.f;
    return *this;
  }
  InstRangeCopier_Indel& KnockoutDeletionMutations() {
    // only insertion mutations remain
    p_defect *= p_defect_is_insertion;
    p_defect_is_insertion = 1.f;
    return *this;
  }

};

} // namespace sgpl

#endif // #ifndef SGPL_SPEC_INSTRANGECOPIER_INDEL_HPP_INCLUDE
