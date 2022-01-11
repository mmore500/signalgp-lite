#pragma once


#ifdef PRODUCTION

#define BACKWARD_HAS_DW 1

#include <stdlib.h>

#include "../../third-party/backward-cpp/backward.hpp"
#include "../../../../third-party/conduit/include/uitsl/nonce/ScopeGuard.hpp"
#include "../../../../third-party/Empirical/include/emp/base/macros.hpp"

namespace bc {
namespace internal {

const uitsl::ScopeGuard source_path_export_guard(
  [](){ setenv(
    "BACKWARD_CXX_SOURCE_PREFIXES",
    EMP_STRINGIFY(SGPL_SOURCE_DIR_),
    0 // won't overwrite
  ); }
);

std::vector<int> make_signals() {
  std::vector<int> signals = backward::SignalHandling::make_default_signals();
  signals.push_back(SIGINT);
  return signals;
}

const backward::SignalHandling backtrace_handler{make_signals()};

} // namespace internal
} // namespace bc


#endif

