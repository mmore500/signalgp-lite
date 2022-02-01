#pragma once
#ifndef SGPL_SPEC_TRANSPOSEWINDOWDISPLACEMENTGENERATOR_PARETO_HPP_INCLUDE
#define SGPL_SPEC_TRANSPOSEWINDOWDISPLACEMENTGENERATOR_PARETO_HPP_INCLUDE

#include <numeric>

#include "../utility/ThreadLocalRandom.hpp"

#include "StarterConfig.hpp"

namespace sgpl {

class TransposeWindowDisplacementGenerator_Pareto {

  float pareto_shape; // "alpha"
  float pareto_scale; // "lambda"

public:

  TransposeWindowDisplacementGenerator_Pareto(
    const float pareto_shape_,
    const float pareto_scale_
  ) : pareto_shape(pareto_shape_)
  , pareto_scale(pareto_scale_)
  { }

  template<typename Config=sgpl::StarterConfig>
  explicit TransposeWindowDisplacementGenerator_Pareto(
    const Config& cfg
  ) : pareto_shape(
    cfg.SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_DISP_PARETO_SHAPE_PARAM()
  ), pareto_scale (
    cfg.SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_DISP_PARETO_SCALE_PARAM()
  ){ }

  TransposeWindowDisplacementGenerator_Pareto()
  : TransposeWindowDisplacementGenerator_Pareto( sgpl::StarterConfig{} )
  { }

  int operator()(
    const size_t num_sites_before_window,
    const size_t num_sites_after_window
  ) const {

    // is this the best way to discretize?
    return std::round(sgpl::tlrand.Get().GetRandZeroSymmetricPareto(
      pareto_shape,
      pareto_scale,
      -static_cast<double>(num_sites_before_window),
      num_sites_after_window
    ));

  }

};

} // namespace sgpl

#endif // #ifndef SGPL_SPEC_TRANSPOSEWINDOWDISPLACEMENTGENERATOR_PARETO_HPP_INCLUDE
