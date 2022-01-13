#pragma once
#ifndef SGPL_UTILITY_REPEATINGNEGATIVEBINOMIALCOUNTDOWN_HPP_INCLUDE
#define SGPL_UTILITY_REPEATINGNEGATIVEBINOMIALCOUNTDOWN_HPP_INCLUDE

#include "../../../third-party/Empirical/include/emp/math/Distribution.hpp"

#include "MemoizeCtor.hpp"
#include "ThreadLocalRandom.hpp"

namespace sgpl {

class RepeatingNegativeBinomialCountdown {

  size_t remaining_count{};

  double p;
  size_t n;

public:

  RepeatingNegativeBinomialCountdown(
    double p_,
    size_t n_=1
  ) : p(p_)
  , n(n_)
  { TestAndStep(); }

  bool TestAndStep() {
    const bool res = !remaining_count;

    if (!remaining_count) {
      auto& distn = sgpl::MemoizeCtor<emp::NegativeBinomial>::lookup(p, n);
      remaining_count = distn.PickRandom( sgpl::tlrand.Get() );
    }

    emp_assert(remaining_count);
    --remaining_count;

    return res;
  }

};

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_REPEATINGNEGATIVEBINOMIALCOUNTDOWN_HPP_INCLUDE
