#pragma once

#include "../utility/CappedSet.hpp"

#include "Core.hpp"
#include "JumpTable.hpp"

namespace sgpl {

template<typename Library>
class Cpu {

  using core_t = sgpl::Core<Library>;

  sgpl::CappedSet<core_t, 16> cores;

  size_t active_core{};

  sgpl::JumpTable<Library> global_jump_table;

  sgpl::JumpTable<Library> local_jump_table_template;

public:

  void ActivateNextCore() { ++active_core %= cores.size(); }

  core_t& GetActiveCore() {
    emp_assert( cores.size() );
    return cores[active_core];
  };

  void KillActiveCore() {
    cores.erase(active_core);
    if (active_core) --active_core;
  }

  void LaunchCore() {
    if ( !cores.full() ) {
      cores.push_back(
        sgpl::Core{ local_jump_table_template, &global_jump_table }
      );
    }
  }

  size_t GetNumCores() const { return cores.size(); }

  size_t GetMaxCores() const { return cores.max_size(); }

  auto begin() { return std::begin( cores ); }

  auto end() { return std::end( cores ); }

  void InitializeAnchors(const sgpl::Program<Library>& program) {
    global_jump_table.InitializeGlobalAnchors( program );
    local_jump_table_template.InitializeLocalAnchors( program );
  }
};


} // namespace sgpl
