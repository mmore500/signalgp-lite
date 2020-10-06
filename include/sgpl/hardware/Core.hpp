#pragma once

#include <limits>

#include "../../../third-party/Empirical/source/base/array.h"

namespace sgpl {

class Core {

  size_t program_counter{};

  // MatchBin<>& local_matchbin;
  //
  // MatchBin<>& global_matchbin;

public:

  emp::array<double, 5> registers;

  void Terminate() { program_counter = std::numeric_limits<size_t>::max(); };

  bool HasTerminated() const {
    return program_counter == std::numeric_limits<size_t>::max();
  }

  size_t GetProgramCounter() const { return program_counter; }

  void AdvanceProgramCounter(const size_t program_length) {
    program_counter += !HasTerminated();
    program_counter %= program_length;
  }

};

} // namespace sgpl
