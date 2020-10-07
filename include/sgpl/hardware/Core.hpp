#pragma once

#include <limits>

#include "../../../third-party/Empirical/source/base/array.h"

#include "JumpTable.hpp"

namespace sgpl {

template<typename Library>
class Core {

  size_t program_counter{};

  sgpl::JumpTable<Library> local_jump_table;

  sgpl::JumpTable<Library>* global_jump_table; // non-owning ptr

  using query_t = typename sgpl::JumpTable<Library>::query_t;

public:

  Core() = default;

  Core(
    const sgpl::JumpTable<Library>& local_jump_table_,
    sgpl::JumpTable<Library>* global_jump_table_
  )
  : local_jump_table(local_jump_table_)
  , global_jump_table(global_jump_table_)
  { ; }

  emp::array<double, 5> registers;

  void Terminate() { program_counter = std::numeric_limits<size_t>::max(); };

  bool HasTerminated() const {
    return program_counter == std::numeric_limits<size_t>::max();
  }

  size_t GetProgramCounter() const { return program_counter; }

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

  void JumpToGlobalAnchorMatch(const query_t& query) {
    const auto res { global_jump_table->Match(query) };
    if ( res.size() ) program_counter = res.front();
  }

  void JumpToLocalAnchorMatch(const query_t& query) {
    const auto res { global_jump_table->Match(query) };
    if ( res.size() ) program_counter = res.front();
  }

};

} // namespace sgpl
