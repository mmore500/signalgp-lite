#pragma once

#include <algorithm>

#include "../../../third-party/Empirical/source/base/array.h"

namespace sgpl {

template<typename Library>
class OpCodeRectifier {

  emp::array< unsigned char, 256> mapper;

public:

  OpCodeRectifier() {

    // TODO intrinsic prevalence

    std::iota( std::begin( mapper ), std::end( mapper ), 0 );

    for (auto& entry : mapper) entry %= Library::GetSize();

  }

  unsigned char Rectify(const unsigned char oc) const { return mapper[oc]; }

};

} // namespace sgpl
