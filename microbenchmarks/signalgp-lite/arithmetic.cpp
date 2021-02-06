#include "sgpl/library/prefab/prefab.hpp"
#include "sgpl/spec/Spec.hpp"

#define OP_LIBRARY Arithmetic

constexpr bool fill_cores = false;

using spec_t = sgpl::Spec<sgpl::ArithmeticOpLibrary>;

#include "benchmark.hpp"
