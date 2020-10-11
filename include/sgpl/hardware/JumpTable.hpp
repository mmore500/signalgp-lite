#pragma once

#include "../utility/EmptyType.hpp"
#include "../program/Program.hpp"

namespace sgpl {

template<typename Spec>
struct JumpTable {

  using match_bin_t = typename Spec::match_bin_t;

  match_bin_t match_bin;

  using tag_t = typename match_bin_t::query_t;

  using library_t = typename Spec::library_t;
  using program_t = sgpl::Program<Spec>;

  inline emp::vector<size_t> MatchRaw(
    const tag_t & query,
    size_t n=std::numeric_limits<size_t>::max()
  ) { return match_bin.MatchRaw(query, n); }

  inline emp::vector<size_t> Match(
    const tag_t & query,
    size_t n=std::numeric_limits<size_t>::max()
  ) { return match_bin.Match(query, n); }

  inline void SetRegulator( const uid_t uid, const double set ) {
    match_bin.SetRegulator(uid, set);
  }

  inline void AdjRegulator( const uid_t uid, const double set ) {
    match_bin.AdjRegulator(uid, set);
  }

  inline double ViewRegulator(const uid_t uid) {
    return match_bin.ViewRegulator(uid);
  }

  inline void Clear() { match_bin.Clear(); }

  inline size_t Size() const { return match_bin.Size(); }

  void InitializeLocalAnchors(const program_t& prog, const size_t start_pos) {
    Clear();
    for (
      size_t pos = (start_pos + 1) % prog.size();
      pos != start_pos
        && !library_t::IsAnchorGlobalOpCode( prog[pos].op_code )
      ;
      ++pos %= prog.size()
    ) {
      const auto& instruction = prog[pos];
      if ( library_t::IsAnchorLocalOpCode( prog[pos].op_code ) ) {
        match_bin.Set( {}, instruction.tag, pos ); // store pos as UID
      }

    }
  }

  void InitializeGlobalAnchors(const sgpl::Program<Spec>& program) {
    Clear();
    for (size_t pos{}; pos < program.size(); ++pos) {
      const auto& instruction = program[pos];
      if ( library_t::IsAnchorGlobalOpCode( instruction.op_code ) ) {
        match_bin.Set( {}, instruction.tag, pos ); // store pos as UID
      }
    }
  }

};


} // namespace sgpl
