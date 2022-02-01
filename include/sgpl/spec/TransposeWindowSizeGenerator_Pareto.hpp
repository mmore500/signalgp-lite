#pragma once
#ifndef SGPL_SPEC_TRANSPOSEWINDOWSIZEGENERATOR_PARETO_HPP_INCLUDE
#define SGPL_SPEC_TRANSPOSEWINDOWSIZEGENERATOR_PARETO_HPP_INCLUDE

#include <numeric>

#include "../utility/ThreadLocalRandom.hpp"

#include "StarterConfig.hpp"

namespace sgpl {

class TransposeWindowSizeGenerator_Pareto {

  float pareto_shape; // "alpha"
  float pareto_scale; // "lambda"

public:

  TransposeWindowSizeGenerator_Pareto(
    const float pareto_shape_,
    const float pareto_scale_
  ) : pareto_shape(pareto_shape_)
  , pareto_scale(pareto_scale_)
  { }

  template<typename Config=sgpl::StarterConfig>
  explicit TransposeWindowSizeGenerator_Pareto(
    const Config& cfg={}
  ) : pareto_shape(
    cfg.SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_DISP_PARETO_SHAPE_PARAM()
  ), pareto_scale (
    cfg.SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_DISP_PARETO_SCALE_PARAM()
  ){ }

  TransposeWindowSizeGenerator_Pareto()
  : TransposeWindowSizeGenerator_Pareto( sgpl::StarterConfig{} )
  { }

  int operator()(const size_t genome_length) const {

    // is this the best way to discretize?
    return std::round( sgpl::tlrand.Get().GetRandLomax(
      pareto_shape,
      pareto_scale,
      genome_length
    ) );

  }

};

} // namespace sgpl

#endif // #ifndef SGPL_SPEC_TRANSPOSEWINDOWSIZEGENERATOR_PARETO_HPP_INCLUDE
