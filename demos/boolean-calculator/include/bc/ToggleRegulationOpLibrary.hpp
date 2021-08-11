#pragma once

#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/operations.hpp"

#include "ToggleableRegulator.hpp"

namespace bc {

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
  bc::ToggleableRegulator<sgpl::global::RegulatorAdj<>>,
  bc::ToggleableRegulator<sgpl::global::RegulatorDecay<>>,
  bc::ToggleableRegulator<sgpl::global::RegulatorGet<>>,
  bc::ToggleableRegulator<sgpl::global::RegulatorSet<>>,
  sgpl::local::Anchor,
  sgpl::local::JumpIf,
  sgpl::local::JumpIfNot,
  bc::ToggleableRegulator<sgpl::local::RegulatorAdj>,
  bc::ToggleableRegulator<sgpl::local::RegulatorDecay>,
  bc::ToggleableRegulator<sgpl::local::RegulatorGet>,
  bc::ToggleableRegulator<sgpl::local::RegulatorSet>,
  sgpl::Decrement,
  sgpl::Increment,
  sgpl::Negate,
  sgpl::Not,
  // sgpl::RandomBool,
  // sgpl::RandomDraw,
  sgpl::Terminal
>;

} // namespace bc
