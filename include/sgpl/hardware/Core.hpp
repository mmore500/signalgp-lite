#pragma once

#include <limits>

#include "../../../third-party/Empirical/source/base/array.h"

#include "../utility/CappedSet.hpp"

#include "JumpTable.hpp"

namespace sgpl {

template<typename Spec>
class Core {

  size_t program_counter{};

  sgpl::JumpTable<Spec, typename Spec::local_matching_t> local_jump_table;

  // non-owning ptr
  sgpl::JumpTable<Spec, typename Spec::global_matching_t>* global_jump_table{};

  using tag_t = typename Spec::tag_t;

public:

  Core() = default;

  Core(
    sgpl::JumpTable<Spec, typename Spec::global_matching_t>& global_jump_table_
  ) : global_jump_table(&global_jump_table_)
  { ; }

  emp::array<float, Spec::num_registers> registers{}; // value initialize

  sgpl::CappedSet<tag_t, Spec::num_fork_requests> fork_requests{};

  inline void Terminate() {
    program_counter = std::numeric_limits<size_t>::max();
  };

  __attribute__ ((hot))
  inline bool HasTerminated() const {
    return program_counter == std::numeric_limits<size_t>::max();
  }

  __attribute__ ((hot))
  inline size_t GetProgramCounter() const { return program_counter; }

  __attribute__ ((hot))
  void AdvanceProgramCounter(const size_t program_length) {
    // equivalent to
    // if ( HasTerminated() == false ) {
    //   ++program_counter;
    //  program_counter %= program_length;
    // }
    const bool has_termianted{ HasTerminated() };
    ++program_counter; // if has terminated, wraps around
    program_counter %= program_length;
    program_counter -= has_termianted;
  }

  inline bool HasLocalAnchors() const { return local_jump_table.GetSize(); }

  inline void LoadLocalAnchors( const sgpl::Program<Spec>& program ) {
    emp_assert( ! HasLocalAnchors() );
    local_jump_table.InitializeLocalAnchors( program, GetProgramCounter() );
  }

  void JumpToGlobalAnchorMatch(const tag_t& query) {
    const auto res { global_jump_table->MatchRegulated(query) };
    if ( res.size() ) program_counter = global_jump_table->GetVal(res.front());
    else Terminate();
    local_jump_table.Clear();
  }

  void JumpToLocalAnchorMatch(const tag_t& query) {
    const auto res { local_jump_table.MatchRegulated(query) };
    if ( res.size() ) program_counter = local_jump_table.GetVal( res.front() );
  }

  inline auto& GetLocalJumpTable() { return local_jump_table; }

  inline auto& GetGlobalJumpTable() { return *global_jump_table; }

  bool RequestFork(const tag_t& tag) {
    return fork_requests.try_push_back( tag );
  }

  void ResetRegisters() { registers.fill( {} ); }

  void Reset() {
    fork_requests.clear();
    ResetRegisters();
    local_jump_table.Clear();
  }

};

} // namespace sgpl
