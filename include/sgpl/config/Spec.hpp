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

};

} // namespace sgpl
