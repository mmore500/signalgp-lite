#pragma once

#include <string>

#include "Empirical/include/emp/config/config.hpp"

namespace bc {

EMP_BUILD_CONFIG(
  Config,

  GROUP(MUTATION, "MUTATION"),
  VALUE(SGPL_PROGRAM_SIZE_CAP,
    size_t, 4096,
    "What size should programs be capped at?"
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
  VALUE(SGPL_SEQMUTATE_MODULE_INDEL_RATE,
    float, 0.01f,
    "How often should module indel mutations occur?"
  ),
  VALUE(SGPL_SEQMUTATE_INST_INDEL_FRAC_INSERTIONS,
    float, 0.5f,
    "What fraction of instruction indel mutations should be insertions?"
  ),
  VALUE(SGPL_SEQMUTATE_INST_INDEL_GARBLE_RATE,
    float, 0.05f,
    "What fraction of instruction indel insertions should be garbled?"
  ),
  VALUE(SGPL_SEQMUTATE_MODULE_INDEL_FRAC_INSERTIONS,
    float, 0.5f,
    "What fraction of module indel mutations should be insertions?"
  ),
  VALUE(SGPL_MUTATION_OCCURENCE_RATE,
    float, 1.0f,
    "How often should mutations happen?"
  ),
  VALUE(REPLICATE,
    size_t, 0,
    "Replicate number (dummy value)"
  ),


  GROUP(OLD_SEQUENCE_MUTATION, "OLD SEQUENCE MUTATION"),
  VALUE(SGPL_MINOR_SEQUENCE_MUTATION_BOUND,
    size_t, 8,
    "TODO"
  ),
  VALUE(SGPL_SEQUENCE_DEFECT_RATE,
    float, 0.001,
    "How often should sloppy copy defect occur?"
  ),


  GROUP(TRANSPOSITION_MUTATION, "TRANSPOSITION MUTATION"),
  VALUE(SGPL_SEQMUTATE_INST_TRANSPOSE_RATE,
    float, 0.0001f,
    "How often per instruction should transpose events arise?"
  ),
  VALUE(SGPL_SEQMUTATE_INST_TRANSPOSE_INVERSION_RATE,
    float, 0.02f,
    "How often should transposed windows be inverted?"
  ),
  VALUE(SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_SIZE_PARETO_SHAPE_PARAM,
    float, 0.5f,
    "Shape parameter (\"alpha\") for distribution of transposed window sizes"
    " when drawn from pareto distribution. "
    "Constrained > 0."
  ),
  VALUE(SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_SIZE_PARETO_SCALE_PARAM,
    float, 2.0f,
    "Scale parameter (\"lambda\") for distribution of transposed window sizes"
    " when drawn from pareto distribution. "
    "Constrained > 0."
  ),
  VALUE(SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_DISP_PARETO_SHAPE_PARAM,
    float, 0.5f,
    "Scale param (\"alpha\") for distn of window transposition displacements"
    " when drawn from pareto distribution. "
    "Constrained > 0."
  ),
  VALUE(SGPL_SEQMUTATE_INST_TRANSPOSE_WINDOW_DISP_PARETO_SCALE_PARAM,
    float, 2.0f,
    "Scale param (\"lambda\") for distn of window transposition displacements"
    " when drawn from pareto distribution. "
    "Constrained > 0."
  ),

  VALUE(UPDATES, size_t, 100, "TODO"),
  VALUE(SEED, size_t, 1, "PRNG Seed"),
  VALUE(LOGGING, bool, false, "Should we log fitness data?"),
  VALUE(LOGGING_FILENAME, std::string, "1", "TODO"),
  VALUE(THRESHOLD_FITNESS, double, 1.0, "TODO"),
  VALUE(DO_REGULATION, bool, true, "TODO"),
  VALUE(TESTING_SET_FILENAME, std::string, "testing_set_prefix.json", "TODO"),
  VALUE(TRAINING_SET_FILENAME, std::string, "training_set_prefix.json", "TODO")
)

static bc::Config config{};

} // namespace bc
