#pragma once
#ifndef SGPL_SPEC_STARTERCONFIG_HPP_INCLUDE
#define SGPL_SPEC_STARTERCONFIG_HPP_INCLUDE

#include "../../../third-party/Empirical/include/emp/config/config.hpp"

namespace sgpl {

EMP_BUILD_CONFIG(
  StarterConfig,

  GROUP(MUTATION, "MUTATION"),
  VALUE(SGPL_PROGRAM_SIZE_CAP,
    size_t, 4096,
    "What should the upper bound on program size be?"
  ),
  VALUE(SGPL_POINTMUTATE_BITFLIP_RATE,
    float, 0.0002f,
    "What fraction of bits should be flipped?"
  ),

  GROUP(INDEL_MUTATION, "INDEL MUTATION"),
  VALUE(SGPL_SEQMUTATE_INST_INDEL_RATE,
    float, 0.001f,
    "How often should instruction indel mutations occur?"
  ),
  VALUE(SGPL_SEQMUTATE_INST_INDEL_FRAC_INSERTIONS,
    float, 0.5f,
    "What fraction of instruction indel mutations should be insertions?"
  ),
  VALUE(SGPL_SEQMUTATE_INST_INDEL_GARBLE_RATE,
    float, 0.05f,
    "What fraction of instruction indel insertions should be garbled?"
  ),
  VALUE(SGPL_SEQMUTATE_MODULE_INDEL_RATE,
    float, 0.005f,
    "How often should module indel mutations occur?"
  ),
  VALUE(SGPL_SEQMUTATE_MODULE_INDEL_FRAC_INSERTIONS,
    float, 0.5f,
    "What fraction of module indel mutations should be insertions?"
  ),

  GROUP(TRANSPOSITION_MUTATION, "TRANSPOSITION MUTATION"),
  VALUE(SGPL_SEQMUTATE_INST_TRANSPOSE_RATE,
    float, 0.0001f,
    "How often per instruction should transpose events arise?"
  ),
  VALUE(SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_SIZE_PARETO_SHAPE_PARAM,
    float, 1.0f,
    "Shape parameter (\"alpha\") for distribution of transposed window sizes"
    " when drawn from pareto distribution. "
    "Constrained > 0."
  ),
  VALUE(SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_SIZE_PARETO_SCALE_PARAM,
    float, 1.0f,
    "Scale parameter (\"lambda\") for distribution of transposed window sizes"
    " when drawn from pareto distribution. "
    "Constrained > 0."
  ),
  VALUE(SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_DISP_PARETO_SHAPE_PARAM,
    float, 1.0f,
    "Scale param (\"alpha\") for distn of window transposition displacements"
    " when drawn from pareto distribution. "
    "Constrained > 0."
  ),
  VALUE(SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_DISP_PARETO_SCALE_PARAM,
    float, 1.0f,
    "Scale param (\"lambda\") for distn of window transposition displacements"
    " when drawn from pareto distribution. "
    "Constrained > 0."
  ),

);

} // namespace sgpl

#endif // #ifndef SGPL_SPEC_STARTERCONFIG_HPP_INCLUDE
