#pragma once
#ifndef SGPL_SPEC_INSTRANGECOPIER_PERFECT_HPP_INCLUDE
#define SGPL_SPEC_INSTRANGECOPIER_PERFECT_HPP_INCLUDE

#include <algorithm>

#include "StarterConfig.hpp"

namespace sgpl {

struct InstRangeCopier_Perfect {

  template<typename Config=sgpl::StarterConfig>
  explicit InstRangeCopier_Perfect(const Config& cfg={})
  { }

  // return additional indels
  template<typename InputIt, typename OutputIt>
  size_t operator()(InputIt first, InputIt last, OutputIt out) const {
    std::copy(first, last, out);
    return 0;
  }

};

} // namespace sgpl

#endif // #ifndef SGPL_SPEC_INSTRANGECOPIER_PERFECT_HPP_INCLUDE
