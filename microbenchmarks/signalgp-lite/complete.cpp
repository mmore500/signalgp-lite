#include "sgpl/library/prefab/prefab.hpp"
#include "sgpl/spec/Spec.hpp"

#define OP_LIBRARY Complete

constexpr bool fill_cores = true;

struct spec_t : public sgpl::Spec<sgpl::CompleteOpLibrary> {

  static constexpr inline size_t switch_steps{ 1 };

};

#include "benchmark.hpp"
