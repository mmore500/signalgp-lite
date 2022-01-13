#pragma once
#ifndef SGPL_SPEC_CONFIG_HPP_INCLUDE
#define SGPL_SPEC_CONFIG_HPP_INCLUDE

#include "../../../third-party/Empirical/include/emp/config/config.hpp"

namespace sgpl {

EMP_BUILD_CONFIG(
  Config,

  GROUP(MUTATION, "MUTATION"),
  VALUE(SGPL_PROGRAM_SIZE_CAP,
    size_t, 4096,
    "What should the upper bound on program size be?"
  ),
  VALUE(SGPL_POINTMUTATE_BITFLIP_RATE,
    float, 0.0002f,
    "What fraction of bits should be flipped?"
  ),
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

);

} // namespace sgpl

#endif // #ifndef SGPL_SPEC_CONFIG_HPP_INCLUDE
