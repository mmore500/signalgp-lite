#pragma once

#include "config.hpp"

namespace bc {

template <typename Operation>
struct ToggleableRegulator {
  static inline Operation op;

  template <typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>& prog,
    typename Spec::peripheral_t& peri
  ) noexcept {
    if (bc::config.DO_REGULATION()) op.run(core, inst, prog, peri);
  }

  static std::string name() { return op.name(); }

  static size_t prevalence() { return op.prevalence(); }

  template <typename Spec>
  static auto descriptors(const sgpl::Instruction<Spec>& inst) {
    return op.descriptors(inst);
  }

  template <typename Spec>
  static auto categories(const sgpl::Instruction<Spec>& inst) {
    return op.categories(inst);
  }
};

} // namespace bc
