#pragma once

#include "config.hpp"

namespace sgpl::demos {

template <typename Operation>
struct ToggleableRegulator {
  //static inline Operation op;

  template <typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>& prog,
    typename Spec::peripheral_t& peri
  ) noexcept {
    if (config.DO_REGULATION()) Operation::run(core, inst, prog, peri);
  }

  static std::string name() { return Operation::name(); }

  static size_t prevalence() { return Operation::prevalence(); }

  template <typename Spec>
  static auto descriptors(const sgpl::Instruction<Spec>& inst) {
    return Operation::descriptors(inst);
  }

  template <typename Spec>
  static auto categories(const sgpl::Instruction<Spec>& inst) {
    return Operation::categories(inst);
  }
};

}; // sgpl::demos
