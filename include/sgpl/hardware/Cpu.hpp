#pragma once
#ifndef SGPL_HARDWARE_CPU_HPP_INCLUDE
#define SGPL_HARDWARE_CPU_HPP_INCLUDE

#include <utility>

#include "../../../third-party/Empirical/source/base/optional.h"

#include "../utility/RingResevoir.hpp"

#include "Core.hpp"
#include "JumpTable.hpp"

namespace sgpl {

template<typename Spec>
class Cpu {

  using core_t = sgpl::Core<Spec>;

  struct impl_ {

    sgpl::RingResevoir<core_t, Spec::num_cores> scheduler;

    size_t active_core_idx{};

    sgpl::JumpTable<Spec, typename Spec::global_matching_t> global_jump_table;

  } data;

  using tag_t = typename Spec::tag_t;

  void RefreshCoreGlobalJumpTablePtrs() {
    for (size_t i{}; i < data.scheduler.GetCapacity(); ++i) {
      data.scheduler.GetBuffer()[i].SetGlobalJumpTable(data.global_jump_table);
    }
  }

public:

  /// Default constructor.
  Cpu() { RefreshCoreGlobalJumpTablePtrs(); }

  /// Copy constructor.
  Cpu(const Cpu& other) : data(other.data) { RefreshCoreGlobalJumpTablePtrs(); }

  /// Move constructor.
  Cpu(Cpu&& other) noexcept : data( std::move(other.data) ) {
    RefreshCoreGlobalJumpTablePtrs();
  }

  /// Copy assignment operator.
  Cpu& operator=(const Cpu& other) { return *this = Cpu(other); }

  /// Move assignment operator.
  Cpu& operator=(Cpu&& other) noexcept {
    std::swap(data, other.data);
    return *this;
  }

  void ActivateNextCore() {
    emp_assert( GetNumBusyCores() );
    ++data.active_core_idx %= GetNumBusyCores();
  }

  bool TryActivateNextCore() {
    if ( HasActiveCore() ) { ActivateNextCore(); return true; }
    else { emp_assert( data.active_core_idx == 0 ); return false; }
  }

  void ActivatePrevCore() {
    emp_assert( GetNumBusyCores() );
    data.active_core_idx += GetNumBusyCores() - 1;
    data.active_core_idx %= GetNumBusyCores();
  }

  bool TryActivatePrevCore() {
    if ( HasActiveCore() ) { ActivatePrevCore(); return true; }
    else { emp_assert( data.active_core_idx == 0 ); return false; }
  }

  __attribute__ ((hot))
  core_t& GetActiveCore() {
    emp_assert( HasActiveCore() );
    return data.scheduler.Get( data.active_core_idx );
  };

  void KillActiveCore() {
    emp_assert( HasActiveCore() );
    for ( const auto& req : GetActiveCore().fork_requests ) {
      if ( !TryLaunchCore(req) ) break;
    }
    data.scheduler.Release(data.active_core_idx);
    TryActivatePrevCore();
  }

  void KillStaleCore() {
    emp_assert( !HasFreeCore() );
    data.scheduler.ReleaseTail();
    // no need to activate prev core, killed core is idx 0
  }

  void DoLaunchCore() {
    emp_assert( HasFreeCore() );
    auto& acquired = data.scheduler.Acquire();
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
    auto& acquired = data.scheduler.Acquire();
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

  size_t GetNumBusyCores() const { return data.scheduler.GetSize(); }

  size_t GetNumFreeCores() const {
    return data.scheduler.GetAvailableCapacity();
  }

  size_t GetMaxCores() const { return data.scheduler.GetCapacity(); }

  __attribute__ ((hot))
  bool HasActiveCore() const { return GetNumBusyCores(); }

  __attribute__ ((hot))
  bool HasFreeCore() const { return GetNumFreeCores(); }

  void Reset() {
    data.scheduler.Reset();
    data.active_core_idx = {};
    data.global_jump_table.Clear();
  }

  void InitializeAnchors(const sgpl::Program<Spec>& program) {
    Reset();
    data.global_jump_table.InitializeGlobalAnchors( program );
  }

};


} // namespace sgpl

#endif // #ifndef SGPL_HARDWARE_CPU_HPP_INCLUDE
