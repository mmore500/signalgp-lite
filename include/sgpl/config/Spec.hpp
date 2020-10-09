#pragma once

#include "../library/prefab/CompleteOpLibrary.hpp"
#include "../utility/EmptyType.hpp"

namespace sgpl {

template<
  typename Library=sgpl::CompleteOpLibrary,
  typename Peripheral=sgpl::EmptyType
>
struct Spec {

  using library_t = Library;

  using peripheral_t = Peripheral;

  static constexpr inline size_t num_cores{ 16 };

  static constexpr inline size_t num_fork_requests{ 3 };

  static constexpr inline size_t num_registers{ 5 };

};

} // namespace sgpl
