#pragma once
#ifndef SGPL_HARDWARE_CPU_HPP_INCLUDE
#define SGPL_HARDWARE_CPU_HPP_INCLUDE

#include "../../../third-party/Empirical/source/base/optional.h"

#include "../utility/RingResevoir.hpp"

#include "Core.hpp"
#include "JumpTable.hpp"

namespace sgpl {

template<typename Spec>
class Cpu {

  using core_t = sgpl::Core<Spec>;

  sgpl::RingResevoir<core_t, Spec::num_cores> scheduler;

  size_t active_core_idx{};

  sgpl::JumpTable<Spec, typename Spec::global_matching_t> global_jump_table;

  using tag_t = typename Spec::tag_t;

public:

  Cpu() { scheduler.Fill( core_t{ global_jump_table } ); }

  void ActivateNextCore() {
    emp_assert( GetNumBusyCores() );
    ++active_core_idx %= GetNumBusyCores();
  }

  bool TryActivateNextCore() {
    if ( HasActiveCore() ) { ActivateNextCore(); return true; }
    else { emp_assert( active_core_idx == 0 ); return false; }
  }

  void ActivatePrevCore() {
    emp_assert( GetNumBusyCores() );
    active_core_idx += GetNumBusyCores() - 1;
    active_core_idx %= GetNumBusyCores();
  }

  bool TryActivatePrevCore() {
    if ( HasActiveCore() ) { ActivatePrevCore(); return true; }
    else { emp_assert( active_core_idx == 0 ); return false; }
  }

  __attribute__ ((hot))
  core_t& GetActiveCore() {
    emp_assert( HasActiveCore() );
    return scheduler.Get( active_core_idx );
  };

  void KillActiveCore() {
    emp_assert( HasActiveCore() );
    for ( const auto& req : GetActiveCore().fork_requests ) {
      if ( !TryLaunchCore(req) ) break;
    }
    scheduler.Release(active_core_idx);
    TryActivatePrevCore();
  }

  void KillStaleCore() {
    emp_assert( !HasFreeCore() );
    scheduler.ReleaseTail();
    // no need to activate prev core, killed core is idx 0
  }

  void DoLaunchCore() {
    emp_assert( HasFreeCore() );
    auto& acquired = scheduler.Acquire();
    acquired.Reset();
  }

  bool TryLaunchCore() {
    if ( ! HasFreeCore() ) return false;
    else { DoLaunchCore(); return true; }
  }

  void ForceLaunchCore() {
    if ( ! HasFreeCore() ) KillStaleCore();
    DoLaunchCore();
  }

  void DoLaunchCore( const tag_t& tag ) {
    emp_assert( HasFreeCore() );
    auto& acquired = scheduler.Acquire();
    acquired.Reset();
    acquired.JumpToGlobalAnchorMatch( tag );
  }

  bool TryLaunchCore( const tag_t& tag ) {
    if ( ! HasFreeCore() ) return false;
    else { DoLaunchCore( tag ); return true; }
  }

  void ForceLaunchCore( const tag_t& tag ) {
    if ( ! HasFreeCore() ) KillStaleCore();
    DoLaunchCore( tag );
  }

  size_t GetNumBusyCores() const { return scheduler.GetSize(); }

  size_t GetNumFreeCores() const {
    return scheduler.GetAvailableCapacity();
  }

  size_t GetMaxCores() const { return scheduler.GetCapacity(); }

  __attribute__ ((hot))
  bool HasActiveCore() const { return GetNumBusyCores(); }

  __attribute__ ((hot))
  bool HasFreeCore() const { return GetNumFreeCores(); }

  void InitializeAnchors(const sgpl::Program<Spec>& program) {
    global_jump_table.InitializeGlobalAnchors( program );
  }

};


} // namespace sgpl

#endif // #ifndef SGPL_HARDWARE_CPU_HPP_INCLUDE
