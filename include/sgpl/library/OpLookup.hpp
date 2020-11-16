#pragma once
#ifndef SGPL_LIBRARY_OPLOOKUP_HPP_INCLUDE
#define SGPL_LIBRARY_OPLOOKUP_HPP_INCLUDE

#include <unordered_map>

#include "../utility/ByteEnumeration.hpp"

namespace sgpl {

template<typename Library>
class OpLookup {

  std::unordered_map<std::string, unsigned char> table;

public:

  OpLookup() {

    #define SGPL_OP_LOOKUP_PAYLOAD(N) \
      if constexpr (N < Library::GetSize()) { \
        using Operation = typename Library::template Operation<N>; \
        table[ Operation::name() ] = N; \
      } \

    static_assert( Library::GetSize() < 256 );

    EMP_WRAP_EACH( SGPL_OP_LOOKUP_PAYLOAD, SGPL_BYTE_ENUMERATION )

    emp_assert(
      table.size() == Library::GetSize(), table.size(), Library::GetSize()
    );

  }

  unsigned char GetOpCode(const std::string op_name) const {
    return table.at(op_name);
  }

  static std::string GetOpName(const size_t op_code) {

    #define SGPL_OP_NAME_PAYLOAD(N) \
      case N: \
        if constexpr (N < Library::GetSize()) { \
          using Operation = typename Library::template Operation<N>; \
          return Operation::name(); \
        } \
      break;

    static_assert( Library::GetSize() < 256 );

    switch( op_code ) {

      EMP_WRAP_EACH( SGPL_OP_NAME_PAYLOAD, SGPL_BYTE_ENUMERATION )

    }

    emp_assert(false, "bad op code");
    throw "bad op code";

  }

  static size_t GetOpPrevalence(const size_t op_code) {

    #define SGPL_OP_PREVALENCE_PAYLOAD(N) \
      case N: \
        if constexpr (N < Library::GetSize()) { \
          using Operation = typename Library::template Operation<N>; \
          return Operation::prevalence(); \
        } \
      break;

    static_assert( Library::GetSize() < 256 );

    switch( op_code ) {

      EMP_WRAP_EACH( SGPL_OP_PREVALENCE_PAYLOAD, SGPL_BYTE_ENUMERATION )

    }

    emp_assert(false, "bad op code");
    throw "bad op code";

  }

  template< typename Instruction >
  static auto GetOpDescriptors(
    const size_t op_code, const Instruction& instruction
  ) {

    #define SGPL_OP_GET_DESCRIPTORS(N) \
      case N: \
        if constexpr (N < Library::GetSize()) { \
          using Operation = typename Library::template Operation<N>; \
          return Operation::descriptors( instruction ); \
        } \
      break;

    static_assert( Library::GetSize() < 256 );

    switch( op_code ) {

      EMP_WRAP_EACH(
        SGPL_OP_GET_DESCRIPTORS, SGPL_BYTE_ENUMERATION
      )

    }

    emp_assert(false, "bad op code");
    throw "bad op code";

  }

};

} // namespace sgpl

#endif // #ifndef SGPL_LIBRARY_OPLOOKUP_HPP_INCLUDE
