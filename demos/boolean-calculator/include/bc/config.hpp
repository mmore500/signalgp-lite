#pragma once

#include <string>

#include "Empirical/include/emp/config/config.hpp"

namespace bc {

EMP_BUILD_CONFIG(
  Config,
  VALUE(SGPL_PROGRAM_MAX_SIZE, size_t, 4096, "What size should programs be capped at?"),

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
    float, 0.01f,
    "How often should module indel mutations occur?"
  ),
  VALUE(SGPL_SEQMUTATE_MODULE_INDEL_FRAC_INSERTIONS,
    float, 0.5f,
    "What fraction of module indel mutations should be insertions?"
  ),
  VALUE(SGPL_MUTATION_OCCURENCE_RATE,
    float, 1.0f,
    "How often should mutations happen?"
  ),

  VALUE(ENVIROMENT_STATES, size_t, 4, "TODO"),
  VALUE(NUMBER_RESPONSES, size_t, 4, "TODO"),
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
