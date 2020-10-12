#pragma once

#include <algorithm>
#include <cstddef>

#include "../../../third-party/cereal/include/cereal/types/vector.hpp"
#include "../../../third-party/Empirical/source/base/vector.h"
#include "../../../third-party/Empirical/source/tools/Random.h"

#include "Instruction.hpp"

namespace sgpl {

template<typename Spec>
struct Program : public emp::vector<sgpl::Instruction<Spec>> {

  Program() = default;

  Program( emp::Random& rand, const size_t n ) {
    std::generate_n(
      std::back_inserter( *this ),
      n,
      [&rand](){ return sgpl::Instruction<Spec>{ rand }; }
    );
  }


};

} // namespace sgpl
