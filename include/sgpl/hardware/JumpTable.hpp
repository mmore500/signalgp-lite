#pragma once

#include "../utility/EmptyType.hpp"
#include "../program/Program.hpp"

namespace sgpl {

template<typename Spec>
struct JumpTable : public Spec::match_bin_t {

  using match_bin_t = typename Spec::match_bin_t;

  using tag_t = typename match_bin_t::query_t;

  using library_t = typename Spec::library_t;

  // inherit parent's constructors
  using match_bin_t::match_bin_t;

  void InitializeLocalAnchors(
    const sgpl::Program<Spec>& program,
    const size_t start_position
  ) {
    this->Clear();
    for (
      size_t pos = (start_position + 1) % program.size();
      pos != start_position
        && !library_t::IsAnchorGlobalOpCode( program[pos].op_code )
      ;
      ++pos %= program.size()
    ) {
      const auto& instruction = program[pos];
      if ( library_t::IsAnchorLocalOpCode( program[pos].op_code ) ) {
        this->Set( {}, instruction.tag, pos ); // store pos as UID
      }

    }
  }

  void InitializeGlobalAnchors(const sgpl::Program<Spec>& program) {
    this->Clear();
    for (size_t pos{}; pos < program.size(); ++pos) {
      const auto& instruction = program[pos];
      if ( library_t::IsAnchorGlobalOpCode( instruction.op_code ) ) {
        this->Set( {}, instruction.tag, pos ); // store pos as UID
      }
    }
  }

};


} // namespace sgpl
