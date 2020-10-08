#pragma once

#include "../../operations/operations.hpp"

#include "../OpLibrary.hpp"

namespace sgpl {

using ArithmeticOpLibrary = sgpl::OpLibrary<
  sgpl::Add,
  sgpl::Divide,
  sgpl::Multiply,
  sgpl::Subtract//,
  // sgpl::Modulo,
  // sgpl::Terminal<>
>;

} // namespace sgpl
