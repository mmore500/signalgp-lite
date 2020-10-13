#pragma once

#include "../program/Program.hpp"
#include "../utility/EmptyType.hpp"

namespace sgpl {

template<typename Spec, typename Impl>
struct JumpTable {

  Impl match_bin;

  using tag_t = typename Impl::query_t;
  using library_t = typename Spec::library_t;
  using program_t = sgpl::Program<Spec>;

  inline auto MatchRaw( const tag_t & query ) {
    return match_bin.MatchRaw(query);
  }

  inline auto MatchRegulated( const tag_t & query ) {
    return match_bin.MatchRegulated(query);
  }

  inline void SetRegulator( const uid_t uid, const double set ) {
    match_bin.SetRegulator(uid, set);
  }

  inline void AdjRegulator( const uid_t uid, const double set ) {
    match_bin.AdjRegulator(uid, set);
  }

  inline double ViewRegulator(const uid_t uid) {
    return match_bin.ViewRegulator(uid);
  }

  inline auto GetVal(const uid_t uid) const { return match_bin.GetVal( uid ); }

  inline void Clear() { match_bin.Clear(); }

  inline size_t GetSize() const { return match_bin.GetSize(); }

  void InitializeLocalAnchors(const program_t& prog, const size_t start_pos) {
    Clear();
    const size_t prog_len{ prog.size() };
    for (
      size_t pos = (start_pos + 1) % prog_len;
      pos != start_pos
        && !library_t::IsAnchorGlobalOpCode( prog[pos].op_code )
      ;
      ++pos %= prog_len
    ) {
      const auto& instruction = prog[pos];
      if ( library_t::IsAnchorLocalOpCode( prog[pos].op_code ) ) {
        match_bin.Put( pos, instruction.tag );
      }

    }
  }

  void InitializeGlobalAnchors(const sgpl::Program<Spec>& program) {
    Clear();
    for (size_t pos{}; pos < program.size(); ++pos) {
      const auto& instruction = program[pos];
      if ( library_t::IsAnchorGlobalOpCode( instruction.op_code ) ) {
        match_bin.Put( pos, instruction.tag );
      }
    }
  }

};


} // namespace sgpl
