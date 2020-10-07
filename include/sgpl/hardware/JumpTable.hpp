#pragma once

#include "../../../third-party/Empirical/source/tools/MatchBin.h"
#include "../../../third-party/Empirical/source/tools/matchbin_utils.h"

#include "../hardware/JumpTable.hpp"
#include "../utility/EmptyType.hpp"
#include "../program/Program.hpp"

namespace sgpl {

using match_bin_t = emp::MatchBin<
  sgpl::EmptyType,
  emp::HammingMetric<32>,
  emp::RankedSelector<std::ratio<32 + 3, 32>>,
  emp::LegacyRegulator
>;

template<typename Library>
struct JumpTable : public match_bin_t  {

  void InitializeLocalAnchors(const sgpl::Program<Library>& program) {
    this->Clear();
    for (size_t pos{}; pos < program.size(); ++pos) {
      const auto& instruction = program[pos];
      if ( Library::IsAnchorLocalOpCode( instruction.op_code ) ) {
        this->Set( {}, instruction.tag, pos ); // store pos as UID
      }
    }
  }

  void InitializeGlobalAnchors(const sgpl::Program<Library>& program) {
    this->Clear();
    for (size_t pos{}; pos < program.size(); ++pos) {
      const auto& instruction = program[pos];
      if ( Library::IsAnchorGlobalOpCode( instruction.op_code ) ) {
        this->Set( {}, instruction.tag, pos ); // store pos as UID
      }
    }
  }


};


} // namespace sgpl
