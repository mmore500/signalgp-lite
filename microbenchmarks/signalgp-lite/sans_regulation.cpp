#include "sgpl/library/prefab/prefab.hpp"
#include "sgpl/spec/Spec.hpp"

#define OP_LIBRARY SansRegulation

constexpr bool fill_cores = true;

struct spec_t : public sgpl::Spec<sgpl::SansRegulationOpLibrary> {

  static constexpr inline size_t switch_steps{ 1 };

};

#include "benchmark.hpp"
