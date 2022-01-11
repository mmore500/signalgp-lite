#pragma once
#ifndef SGPL_ALGORITHM_MODULE_INDEL_COPY_HPP_INCLUDE
#define SGPL_ALGORITHM_MODULE_INDEL_COPY_HPP_INCLUDE

#include <cmath>
#include <limits>
#include <tuple>
#include <utility>

#include "../../../third-party/conduit/include/uitsl/debug/audit_cast.hpp"
#include "../../../third-party/Empirical/include/emp/base/vector.hpp"
#include "../../../third-party/Empirical/include/emp/math/Distribution.hpp"
#include "../../../third-party/Empirical/include/emp/math/math.hpp"

#include "../program/GlobalAnchorIterator.hpp"
#include "../program/Program.hpp"
#include "../utility/ThreadLocalRandom.hpp"

namespace sgpl {

  template <typename Container>
  using module_indel_copy_res_t = std::tuple<
    Container,
    size_t // cumulative num sites inserted and/or deleted
  >;

  template <typename Container, typename ModuleIterator>
  sgpl::module_indel_copy_res_t<Container> module_indel_copy(
    const Container& original,
    const float p_defect,
    const size_t res_size_limit=std::numeric_limits<size_t>::max()
  ) {

    module_indel_copy_res_t< Container > res{};
    auto& res_vector = std::get<0>(res);
    res_vector.reserve( original.size() );
    auto& cumulative_insertion_deletion = std::get<1>(res);

    const auto program_begin = ModuleIterator::make_begin(original);
    const auto program_end = ModuleIterator::make_end(original);

    auto stern_it = program_begin;
    auto aft_it = program_begin;
    if (program_begin != program_end) do {

      stern_it = std::exchange( aft_it, std::next(aft_it) );

      using inst_it_t = typename Container::const_iterator;
      const auto cur_module_begin = static_cast<inst_it_t>(stern_it);
      const auto cur_module_end = static_cast<inst_it_t>(aft_it);
      const size_t cur_module_length = std::distance(
        cur_module_begin,
        cur_module_end
      );

      // draw number of module copies to copy into result
      const double outcome = sgpl::tlrand.Get().GetDouble(-1.0, 1.0);
      const bool do_indel = std::fabs(outcome) < p_defect;
      const size_t num_module_copies = 1 + do_indel * emp::Sgn(outcome);

      if (do_indel) cumulative_insertion_deletion += cur_module_length;

      // copy module into result n times
      for (size_t i{}; i < num_module_copies; ++i) {
        emp_assert( res_size_limit >= res_vector.size() );
        const size_t n = std::min(
          cur_module_length,
          res_size_limit - res_vector.size()
        );
        std::copy_n(
          cur_module_begin,
          n,
          std::back_inserter( res_vector )
        );
      }

    } while ( aft_it != program_end );

    return res;

  }

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_MODULE_INDEL_COPY_HPP_INCLUDE
