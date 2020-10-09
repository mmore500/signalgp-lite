#include "sgpl/config/Spec.hpp"
#include "sgpl/library/prefab/prefab.hpp"

#define OP_LIBRARY Arithmetic

constexpr bool fill_cores = false;

using spec_t = sgpl::Spec<sgpl::ArithmeticOpLibrary>;

#include "benchmark.hpp"
