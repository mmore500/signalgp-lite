#pragma once

#include <tuple>

#include "../hardware/Core.hpp"
#include "../operations/operations.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

using Library = std::tuple<
  sgpl::Terminate,
  sgpl::Nop,
  sgpl::Add,
  sgpl::Decrement,
  sgpl::Increment,
  sgpl::Not,
  sgpl::Subtract
>;

} // namespace sgpl
