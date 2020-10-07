#pragma once

#include <tuple>

#include "../../../third-party/conduit/include/uitsl/meta/tuple_index.hpp"

#include "../hardware/Core.hpp"
#include "../operations/operations.hpp"

namespace sgpl {

using op_library_parent_t = std::tuple<
  sgpl::Terminate,
  sgpl::Nop,
  sgpl::Add,
  sgpl::Decrement,
  sgpl::Increment,
  sgpl::Not,
  sgpl::Subtract,
  sgpl::AnchorGlobal,
  sgpl::AnchorLocal,
  sgpl::JumpIfGlobal,
  sgpl::JumpIfLocal
>;

struct OpLibrary : public op_library_parent_t {

  constexpr static bool IsAnchorLocalOpCode(const size_t op_code) {

    constexpr size_t anchor_local_op_code
      = uitsl::tuple_index<sgpl::AnchorLocal, op_library_parent_t>::value;

    return op_code == anchor_local_op_code;

  }

  constexpr static bool IsAnchorGlobalOpCode(const size_t op_code) {

    constexpr size_t anchor_global_op_code
      = uitsl::tuple_index<sgpl::AnchorGlobal, op_library_parent_t>::value;

    return op_code == anchor_global_op_code;

  }

  constexpr static size_t GetSize() {
    return std::tuple_size<op_library_parent_t>();
  }

  template<size_t I>
  using Operation = typename std::tuple_element<I, op_library_parent_t>::type;


};

} // namespace sgpl
