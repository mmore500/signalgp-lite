#pragma once

#include "../../../third-party/Empirical/source/tools/Random.h"

namespace sgpl {

class ThreadLocalRandom {

  inline static thread_local emp::Random rand{};

public:

  static thread_local emp::Random& Get() { return rand; }

};


} // namespace sgpl
