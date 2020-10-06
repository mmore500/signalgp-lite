#pragma once

#include <tuple>

#include "../hardware/Core.hpp"
#include "../operations/instructions.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

using Library = std::tuple<
  sgpl::Add,
  sgpl::Decrement,
  sgpl::Increment,
  sgpl::Not,
  sgpl::Subtract
>;

} // namespace sgpl
