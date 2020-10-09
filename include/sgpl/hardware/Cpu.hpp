#pragma once

#include "../../../third-party/Empirical/source/base/optional.h"

#include "../utility/Resevoir.hpp"

#include "Core.hpp"
#include "JumpTable.hpp"

namespace sgpl {

template<typename Spec>
class Cpu {

  using core_t = sgpl::Core<Spec>;

  emp::array<core_t, Spec::num_cores> cores;

  sgpl::Resevoir<typename decltype(cores)::iterator, Spec::num_cores> threads;

  size_t active_thread{};

  emp::optional< sgpl::JumpTable<Spec> > global_jump_table;

  sgpl::JumpTable<Spec> local_jump_table_template;

  using tag_t = typename sgpl::JumpTable<Spec>::tag_t;

public:

  Cpu() {
    std::iota(
      std::begin( threads.array() ),
      std::end( threads.array() ),
      std::begin(cores)
    );
    cores.fill( core_t{ *global_jump_table} );
  }

  void ActivateNextCore() { ++active_thread %= threads.size(); }

  core_t& GetActiveCore() {
    emp_assert( threads.size() );
    return *threads[active_thread];
  };

  void KillActiveCore() {

    for ( const auto& request : threads[ active_thread ]->fork_requests ) {
      LaunchCore( request );
    }
    threads.release(active_thread);
    if (active_thread) --active_thread; // todo fixme
  }

  void LaunchCore() {
    if ( !threads.full() ) {
      threads.acquire();
      threads.back()->Reset();
    }
  }

  void LaunchCore( const tag_t& tag ) {
    if ( !threads.full() ) {
      threads.acquire();
      threads.back()->Reset();
      threads.back()->JumpToGlobalAnchorMatch( tag );
    }
  }

  size_t GetNumCores() const { return threads.size(); }

  size_t GetNumFreeCores() const { return Spec::num_cores - threads.size(); }

  size_t GetMaxCores() const { return threads.max_size(); }

  auto begin() { return std::begin( threads ); }

  auto end() { return std::end( threads ); }

  void InitializeAnchors(const sgpl::Program<Spec>& program) {
    global_jump_table.emplace();
    global_jump_table->InitializeGlobalAnchors( program );
  }

};


} // namespace sgpl
