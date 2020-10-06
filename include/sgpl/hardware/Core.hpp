#pragma once

#include "../../../third-party/Empirical/source/base/array.h"

namespace sgpl {

struct Core {

  size_t inst_counter;

  // MatchBin<>& local_matchbin;
  //
  // MatchBin<>& global_matchbin;

  emp::array<double, 5> registers;

};

} // namespace sgpl
