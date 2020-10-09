#pragma once

#include "../../../third-party/Empirical/source/tools/MatchBin.h"
#include "../../../third-party/Empirical/source/tools/matchbin_utils.h"

#include "../library/prefab/CompleteOpLibrary.hpp"
#include "../utility/EmptyType.hpp"

namespace sgpl {

template<
  typename Library=sgpl::CompleteOpLibrary,
  typename Peripheral=sgpl::EmptyType
>
struct Spec {

  using library_t = Library;

  using peripheral_t = Peripheral;

  using match_bin_t = emp::MatchBin<
    sgpl::EmptyType,
    emp::HammingMetric<32>,
    emp::RankedSelector<std::ratio<16+8, 16>>,
    emp::AdditiveCountdownRegulator<>
  >;

  static constexpr inline size_t num_cores{ 16 };

  static constexpr inline size_t num_fork_requests{ 3 };

  static constexpr inline size_t num_registers{ 5 };

  // maximum num steps executed on one core before next core is executed
  static constexpr inline size_t switch_steps{ 8 };

};

} // namespace sgpl
