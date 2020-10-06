#pragma once

#include "../utility/CappedSet.hpp"

#include "Core.hpp"

namespace sgpl {

class Cpu {

  sgpl::CappedSet<sgpl::Core, 16> cores;

  size_t active_core{};

public:

  void ActivateNextCore() { active_core = (active_core + 1) % cores.size(); }

  Core* GetActiveCoreOrNullptr() {
    return cores.size() ? &cores[active_core] : nullptr;
  }

  void KillActiveCore() {
    cores.erase(active_core);
    if (active_core) --active_core;
  }

  void LaunchCore() { if ( !cores.full() ) cores.push_back( sgpl::Core{} ); }

};


} // namespace sgpl
