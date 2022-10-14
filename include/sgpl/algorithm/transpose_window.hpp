#pragma once
#ifndef SGPL_ALGORITHM_TRANSPOSE_WINDOW_HPP_INCLUDE
#define SGPL_ALGORITHM_TRANSPOSE_WINDOW_HPP_INCLUDE

#include <algorithm>
#include <cassert>
#include <iterator>
#include <tuple>
#include <utility>

#include "../algorithm/next.hpp"
#include "../algorithm/prev.hpp"
#include "../spec/TransposeWindowDisplacementGenerator_Default.hpp"
#include "../spec/TransposeWindowSizeGenerator_Default.hpp"
#include "../utility/random_between.hpp"
#include "../utility/ThreadLocalRandom.hpp"

#include "slide_n.hpp"

namespace sgpl {

namespace impl {

template <
  typename RandomIt,
  typename WindowDisplacementGenerator
>
std::tuple<RandomIt, RandomIt, RandomIt> transpose_window(
  const RandomIt genome_first,
  const RandomIt genome_last,
  const RandomIt window_first,
  const RandomIt window_last,
  const WindowDisplacementGenerator& window_displacement_generator
) {

  assert(genome_first <= window_first);
  assert(window_first <= window_last);
  assert(window_last <= genome_last);

  const int num_sites_before_window
    = std::distance(genome_first, window_first);
  const int num_sites_after_window
    = std::distance(window_last, genome_last);

  const int displacement = window_displacement_generator(
    num_sites_before_window,
    num_sites_after_window
  );

  const RandomIt transposed_window_first = sgpl::slide_n(
    window_first, window_last,
    displacement
  );

  const size_t window_width = std::distance(window_first, window_last);
  const RandomIt transposed_window_last = std::next(
    transposed_window_first, window_width
  );

  return {window_first, transposed_window_first, transposed_window_last};

}

} // namespace impl

template <
  typename RandomIt,
  typename WindowDisplacementGenerator,
  typename WindowSizeGenerator
>
std::tuple<RandomIt, RandomIt, RandomIt> transpose_window(
  const RandomIt genome_first,
  const RandomIt genome_last,
  const RandomIt target_site,
  const WindowDisplacementGenerator& window_displacement_generator,
  const WindowSizeGenerator& window_size_generator
) {

  assert(genome_first <= target_site);
  assert(target_site <= genome_last);

  const size_t num_genome_sites = std::distance(
    genome_first,
    genome_last
  );
  const size_t window_size = window_size_generator(num_genome_sites);

  // window must contain target site
  const RandomIt leftmost_legal_window_first = sgpl::prev(
    target_site, genome_first, window_size
  );
  const RandomIt rightmost_legal_window_first = std::min(
    std::prev(genome_last, window_size),
    sgpl::next(target_site, genome_last, window_size)
  );


  const RandomIt window_first = sgpl::random_between(
    leftmost_legal_window_first,
    rightmost_legal_window_first
  );
  const RandomIt window_last = std::next(window_first, window_size);

  return sgpl::impl::transpose_window<RandomIt, WindowDisplacementGenerator>(
    genome_first,
    genome_last,
    window_first,
    window_last,
    window_displacement_generator
  );

}

/// Transpose one window of elements within a range.
/// @return tuple of iterators
///  1. before position of transposed window first
///  2. after position of transposed window first
///  2. after position of transposed window last
template <
  typename RandomIt,
  typename WindowDisplacementGenerator
    =sgpl::TransposeWindowDisplacementGenerator_Default,
  typename WindowSizeGenerator
    =sgpl::TransposeWindowSizeGenerator_Default
>
std::tuple<RandomIt, RandomIt, RandomIt> transpose_window(
  const RandomIt genome_first,
  const RandomIt genome_last,
  const WindowDisplacementGenerator window_displacement_generator={},
  const WindowSizeGenerator window_size_generator={}
) {

  const RandomIt target_site = sgpl::random_between(
    genome_first,
    genome_last
  );

  return sgpl::transpose_window<
    RandomIt, WindowDisplacementGenerator, WindowSizeGenerator
  >(
    genome_first,
    genome_last,
    target_site,
    window_displacement_generator,
    window_size_generator
  );

}

} // namespace sgpl

#endif // #ifndef SGPL_ALGORITHM_TRANSPOSE_WINDOW_HPP_INCLUDE
