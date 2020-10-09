#pragma once

#include "../../../third-party/Empirical/source/base/optional.h"

#include "../utility/CappedSet.hpp"

#include "Core.hpp"
#include "JumpTable.hpp"

namespace sgpl {

template<typename Spec>
class Cpu {

  using core_t = sgpl::Core<Spec>;

  sgpl::CappedSet<core_t, Spec::num_cores> cores;

  size_t active_core{};

  emp::optional< sgpl::JumpTable<Spec> > global_jump_table;

  sgpl::JumpTable<Spec> local_jump_table_template;

  using tag_t = typename sgpl::JumpTable<Spec>::tag_t;

public:

  void ActivateNextCore() { ++active_core %= cores.size(); }

  core_t& GetActiveCore() {
    emp_assert( cores.size() );
    return cores[active_core];
  };

  void KillActiveCore() {

    for ( const auto& request : cores[ active_core ].fork_requests ) {
      LaunchCore( request );
    }
    cores.erase(active_core);
    if (active_core) --active_core;
  }

  void LaunchCore() {
    if ( !cores.full() ) cores.push_back( sgpl::Core{ *global_jump_table } );
  }

  void LaunchCore( const tag_t& tag ) {
    if ( !cores.full() ) {
      cores.push_back( sgpl::Core{ *global_jump_table } );
      cores.back().JumpToGlobalAnchorMatch( tag );
    }
  }

  size_t GetNumCores() const { return cores.size(); }

  size_t GetNumFreeCores() const { return Spec::num_cores - cores.size(); }

  size_t GetMaxCores() const { return cores.max_size(); }

  auto begin() { return std::begin( cores ); }

  auto end() { return std::end( cores ); }

  void InitializeAnchors(const sgpl::Program<Spec>& program) {
    global_jump_table.emplace();
    global_jump_table->InitializeGlobalAnchors( program );
  }

};


} // namespace sgpl
