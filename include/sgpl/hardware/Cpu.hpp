#pragma once

#include "../utility/CappedSet.hpp"

#include "Core.hpp"

namespace sgpl {

class Cpu {

  sgpl::CappedSet<sgpl::Core, 16> cores;

  size_t active_core{};

public:

  void ActivateNextCore() { ++active_core %= cores.size(); }

  Core& GetActiveCore() {
    emp_assert( cores.size() );
    return cores[active_core];
  };

  Core* GetActiveCoreOrNullptr() {
    return cores.size() ? &cores[active_core] : nullptr;
  }

  void KillActiveCore() {
    cores.erase(active_core);
    if (active_core) --active_core;
  }

  void LaunchCore() { if ( !cores.full() ) cores.push_back( sgpl::Core{} ); }

  size_t GetNumCores() const { return cores.size(); }

  size_t GetMaxCores() const { return cores.max_size(); }

  auto begin() { return std::begin( cores ); }

  auto end() { return std::end( cores ); }

};


} // namespace sgpl
