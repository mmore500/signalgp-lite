#pragma once

#include "../include/sgpl/operations/operations.hpp"

#include "../include/sgpl/library/OpLibrary.hpp"

#include "ToggleableRegulator.hpp"

namespace sgpl {

using ToggleRegulationOpLibrary = sgpl::OpLibrary<
  sgpl::ForkIf,
  sgpl::Nop<0>,
  sgpl::Nop<1>,
  sgpl::Nop<2>,
  sgpl::TerminateIf,
  sgpl::Add,
  sgpl::Divide,
  sgpl::Modulo,
  sgpl::Multiply,
  sgpl::Subtract,
  sgpl::BitwiseAnd,
  sgpl::BitwiseNot,
  sgpl::BitwiseOr,
  sgpl::BitwiseShift,
  sgpl::BitwiseXor,
  sgpl::CountOnes,
  // sgpl::RandomFill,
  sgpl::Equal,
  sgpl::GreaterThan,
  sgpl::LessThan,
  sgpl::LogicalAnd,
  sgpl::LogicalOr,
  sgpl::NotEqual,
  sgpl::global::Anchor,
  sgpl::global::JumpIf,
  sgpl::global::JumpIfNot,
  sgpl::demos::ToggleableRegulator<sgpl::global::RegulatorAdj<>>,
  sgpl::demos::ToggleableRegulator<sgpl::global::RegulatorDecay<>>,
  sgpl::demos::ToggleableRegulator<sgpl::global::RegulatorGet<>>,
  sgpl::demos::ToggleableRegulator<sgpl::global::RegulatorSet<>>,
  sgpl::local::Anchor,
  sgpl::local::JumpIf,
  sgpl::local::JumpIfNot,
  sgpl::demos::ToggleableRegulator<sgpl::local::RegulatorAdj>,
  sgpl::demos::ToggleableRegulator<sgpl::local::RegulatorDecay>,
  sgpl::demos::ToggleableRegulator<sgpl::local::RegulatorGet>,
  sgpl::demos::ToggleableRegulator<sgpl::local::RegulatorSet>,
  sgpl::Decrement,
  sgpl::Increment,
  sgpl::Negate,
  sgpl::Not,
  // sgpl::RandomBool,
  // sgpl::RandomDraw,
  sgpl::Terminal
>;

} // namespace sgpl
