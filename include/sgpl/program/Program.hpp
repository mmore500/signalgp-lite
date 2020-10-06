#pragma once

#include <algorithm>
#include <cstddef>

#include "../../../third-party/Empirical/source/base/vector.h"
#include "../../../third-party/Empirical/source/tools/Random.h"

#include "Instruction.hpp"

namespace sgpl {

struct Program : public emp::vector<sgpl::Instruction> {

  Program( emp::Random& rand, const size_t n ) {
    std::generate_n(
      std::back_inserter( *this ),
      n,
      [&rand](){ return sgpl::Instruction{ rand }; }
    );
  }


};

} // namespace sgpl
