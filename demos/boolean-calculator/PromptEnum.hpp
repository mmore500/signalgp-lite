#pragma once

#include "third-party/magic_enum/include/magic_enum.hpp"

namespace sgpl::demos {

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

} // namespace sgpl::demos

// adapted from https://stackoverflow.com/a/40006041
namespace cereal {

  template <class Archive> inline
  std::string save_minimal(
    Archive const &, sgpl::demos::PromptEnum const & t
  ) {
    return std::string(
      magic_enum::enum_name(t)
    );
  }

  template <class Archive> inline
  void load_minimal(
    Archive const &, sgpl::demos::PromptEnum & t, std::string const & value
  ) {
    t = *magic_enum::enum_cast<sgpl::demos::PromptEnum>( value );
  }

} // namespace cereal
