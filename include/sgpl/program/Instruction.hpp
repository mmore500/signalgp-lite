#pragma once

#include <algorithm>
#include <cstddef>

#include "../../../third-party/Empirical/source/base/array.h"
#include "../../../third-party/Empirical/source/tools/BitSet.h"
#include "../../../third-party/Empirical/source/tools/Random.h"

namespace sgpl {

struct Instruction {

  size_t op_code;

  emp::array<size_t, 3> args;

  emp::BitSet<32> tag;

  Instruction() = default;

  Instruction(emp::Random& rand)
  : op_code( rand.GetUInt( 7 ) )
  , tag( rand )
  {
    std::generate(
      std::begin( args ),
      std::end( args ),
      [&rand](){ return rand.GetUInt( 5 ); }
    );
  }

};

} // namespace sgpl
