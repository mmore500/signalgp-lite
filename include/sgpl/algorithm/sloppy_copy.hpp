#pragma once
#ifndef SGPL_ALGORITHM_SLOPPY_COPY_HPP_INCLUDE
#define SGPL_ALGORITHM_SLOPPY_COPY_HPP_INCLUDE

#include <limits>
#include <tuple>
#include <utility>

#include "../../../third-party/conduit/include/uitsl/debug/audit_cast.hpp"

#include "../utility/RepeatingNegativeBinomialCountdown.hpp"
#include "../utility/ThreadLocalRandom.hpp"

namespace sgpl {

  template< typename T , bool Scramble=false >
  auto sloppy_copy(
    const T& original,
    const float p_defect,
    const std::pair<size_t, size_t> defect_bounds,
    const size_t res_size_limit=std::numeric_limits<size_t>::max()
  ) {

    std::tuple<T, size_t> res{};
    auto& res_vector = std::get<0>(res);
    auto& cumulative_insertion_deletion = std::get<1>(res);

    if (p_defect == 0) { // bail early to avoid crash when p = 0
      res_vector = original;
      cumulative_insertion_deletion = 0;
      return res;
    }

    std::get<0>(res).reserve( original.size() );

    sgpl::RepeatingNegativeBinomialCountdown defect_countdown(p_defect, 1);

    // if we wanted to make the process uniform across a circular genome,
    // then we would draw this from [0, original.size())
    const size_t offset{};

    int scramble_countdown{};

    for (int idx{}; idx < uitsl::audit_cast<int>( original.size() ); ++idx) {

      if (defect_countdown.TestAndStep()) {
        const int defect = sgpl::tlrand.Get().GetInt(
          defect_bounds.first, defect_bounds.second
        );
        idx += defect;
        cumulative_insertion_deletion += std::abs( defect );

        // scramble insertion mutations
        if constexpr ( Scramble ) {
          scramble_countdown += -defect;
          scramble_countdown = std::max( scramble_countdown, 0 );
        }

      }


      if ( Scramble && scramble_countdown ) {
        --scramble_countdown;
        // don't require this ctor if not Scrambling
        if constexpr ( Scramble ) res_vector.emplace_back(
          sgpl::tlrand.Get()
        );
      } else res_vector.push_back(
        original[ (idx + offset) % original.size() ]
      );

      // enforce maximum result size
      if ( res_vector.size() >= res_size_limit ) break;

    }

    return res;

  }

  template< typename T, bool Scramble=false >
  auto sloppy_copy(
    const T& original,
    const float p_defect,
    const size_t defect_bound,
    const size_t res_size_limit=std::numeric_limits<size_t>::max()
  ) {

    return sgpl::sloppy_copy<T, Scramble>(
      original,
      p_defect,
      { -defect_bound, defect_bound },
      res_size_limit
    );

  }

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_SLOPPY_COPY_HPP_INCLUDE
