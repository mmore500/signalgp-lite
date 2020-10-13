#pragma once

#include "../../../third-party/Empirical/source/base/vector.h"
#include "../../../third-party/Empirical/source/tools/Distribution.h"

#include "../utility/ThreadLocalRandom.hpp"

namespace sgpl {

  template< typename T , size_t TemplatedInstance=0 >
  emp::vector<T> sloppy_copy(
    const emp::vector<T>& original,
    const float p_defect,
    const size_t defect_bound
  ) {

    emp::vector<T> res;
    res.reserve( original.size() );

    // TODO cache based on p_defect
    thread_local emp::NegativeBinomial neg_bino( p_defect, 1 );
    neg_bino.Setup(p_defect, 1);

    size_t defect_countdown = neg_bino.PickRandom(
      sgpl::ThreadLocalRandom::Get()
    );

    // if we wanted to make the process uniform across a circular genome,
    // then we would draw this from [0, original.size())
    const size_t offset = 0;

    // TODO audit_cast
    for (int idx{}; idx < static_cast<int>( original.size() ); ++idx) {

      if (--defect_countdown == 0) {
        idx += sgpl::ThreadLocalRandom::Get().GetInt(
          -defect_bound, defect_bound
        );
        defect_countdown = neg_bino.PickRandom(
          sgpl::ThreadLocalRandom::Get()
        );
      }

      res.push_back( original[ (idx + offset) % original.size() ] );

    }

    return res;

  }

}
