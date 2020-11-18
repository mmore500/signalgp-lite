#pragma once
#ifndef SGPL_PROGRAM_OPCODERECTIFIER_HPP_INCLUDE
#define SGPL_PROGRAM_OPCODERECTIFIER_HPP_INCLUDE

#include <algorithm>

#include "../../../third-party/Empirical/source/base/array.h"

namespace sgpl {

template<typename Library>
class OpCodeRectifier {

  emp::array< unsigned char, 256> mapper;

public:

  OpCodeRectifier() {

    emp_assert( Library::GetSize() );

    size_t rep_countdown{};
    unsigned char op_code{ Library::GetSize() - 1 };
    for (size_t mapper_idx{}; mapper_idx < mapper.size(); ++mapper_idx ) {

      if (rep_countdown == 0) {
        ++op_code %= Library::GetSize();
        rep_countdown = Library::GetOpPrevalence( op_code );
        if ( rep_countdown == 0 ) { --mapper_idx; continue; }
      }

      mapper[ mapper_idx ] = op_code;

      --rep_countdown;

    }

  }

  unsigned char Rectify(const unsigned char oc) const { return mapper[oc]; }

};

} // namespace sgpl

#endif // #ifndef SGPL_PROGRAM_OPCODERECTIFIER_HPP_INCLUDE
