#pragma once

#include <tuple>

#include "../../../third-party/conduit/include/uitsl/meta/tuple_index.hpp"
#include "../../../third-party/conduit/include/uitsl/meta/tuple_has_type.hpp"

namespace sgpl {

template<typename... Ops>
struct OpLibrary : public std::tuple<Ops...> {

  using op_library_parent_t = std::tuple<Ops...>;

  constexpr static bool IsAnchorLocalOpCode(const size_t op_code) {
    if constexpr (
      uitsl::tuple_has_type<sgpl::local::Anchor, op_library_parent_t>::value
    ) {

      constexpr size_t anchor_local_op_code
        = uitsl::tuple_index<sgpl::local::Anchor, op_library_parent_t>::value;
      return op_code == anchor_local_op_code;

    } else return false;


  }

  constexpr static bool IsAnchorGlobalOpCode(const size_t op_code) {

    if constexpr (
      uitsl::tuple_has_type<sgpl::global::Anchor, op_library_parent_t>::value
    ) {

      constexpr size_t anchor_global_op_code
        = uitsl::tuple_index<sgpl::global::Anchor, op_library_parent_t>::value;
      return op_code == anchor_global_op_code;

    } else return false;

  }

  constexpr static size_t GetSize() {
    return std::tuple_size<op_library_parent_t>();
  }

  template<size_t I>
  using Operation = typename std::tuple_element<I, op_library_parent_t>::type;


};

} // namespace sgpl
