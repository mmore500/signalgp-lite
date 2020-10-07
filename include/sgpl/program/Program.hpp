#pragma once

#include <algorithm>
#include <cstddef>

#include "../../../third-party/Empirical/source/base/vector.h"
#include "../../../third-party/Empirical/source/tools/Random.h"

#include "Instruction.hpp"

namespace sgpl {

template<typename Library>
struct Program : public emp::vector<sgpl::Instruction<Library>> {

  Program( emp::Random& rand, const size_t n ) {
    std::generate_n(
      std::back_inserter( *this ),
      n,
      [&rand](){ return sgpl::Instruction<Library>{ rand }; }
    );
  }


};

} // namespace sgpl
