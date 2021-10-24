#pragma once

#include "../third-party/Empirical/include/emp/config/config.hpp"

EMP_BUILD_CONFIG(
  Config,
  VALUE(SGPL_PROGRAM_MAX_SIZE, size_t, 4096, "What size should programs be capped at?"),
  VALUE(SGPL_SEVERE_SEQUENCE_MUTATION_RATE, float, 0.001, "TODO"),
  VALUE(SGPL_MINOR_SEQUENCE_MUTATION_BOUND, size_t, 8, "TODO"),
  VALUE(SGPL_POINT_MUTATION_RATE, float, 0.0002, "What fraction of bits should be scrambled?"),
  VALUE(SGPL_SEQUENCE_DEFECT_RATE, float, 0.001, "How often should sloppy copy defect occur?"),
  VALUE(SGPL_MUTATION_OCCURENCE_RATE, float, 0.5, "How often should mutations happen?"),
  VALUE(ENVIROMENT_STATES, size_t, 4, "TODO"),
  VALUE(NUMBER_RESPONSES, size_t, 4, "TODO"),
  VALUE(UPDATES, size_t, 100, "TODO"),
  VALUE(SEED, size_t, 1, "PRNG Seed"),
  VALUE(LOGGING, bool, false, "Should we log fitness data?"),
  VALUE(LOGGING_FILENAME, size_t, 1, "TODO"),
  VALUE(THRESHOLD_FITNESS, size_t, 16, "TODO"),
  VALUE(DO_REGULATION, bool, true, "TODO")
)

static Config config{};
