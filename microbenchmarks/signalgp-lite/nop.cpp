#include "sgpl/config/Spec.hpp"
#include "sgpl/library/prefab/prefab.hpp"

#define OP_LIBRARY Nop

constexpr bool fill_cores = false;

using spec_t = sgpl::Spec<sgpl::NopOpLibrary>;

#include "benchmark.hpp"
