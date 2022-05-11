#pragma once

#include "magic_enum/include/magic_enum.hpp"

namespace bc {

enum class PromptEnum {
  AND,
  ANDNOT,
  ECHO,
  EQU,
  NAND,
  NOT,
  NUM,
  NOR,
  OR,
  ORNOT,
  XOR
};

} // namespace bc

// adapted from https://stackoverflow.com/a/40006041
namespace cereal {

  template <class Archive> inline
  std::string save_minimal(
    Archive const &, bc::PromptEnum const & t
  ) {
    return std::string(
      magic_enum::enum_name(t)
    );
  }

  template <class Archive> inline
  void load_minimal(
    Archive const &, bc::PromptEnum & t, std::string const & value
  ) {
    t = *magic_enum::enum_cast<bc::PromptEnum>( value );
  }

} // namespace cereal
