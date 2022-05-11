#pragma once



#include "Empirical/include/emp/base/vector.hpp"
#include "Empirical/include/emp/Evolve/World.hpp"

#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"


namespace bc {

template <typename Organism>
std::vector<typename Organism::program_t> SerializeWorld(emp::World<Organism>& world) {
  std::vector<typename Organism::program_t> programs;

  std::transform(
    world.begin(),
    world.end(),
    std::back_inserter(programs),
    [](auto& org) {
      return org.program;
    }
  );

  return programs;
}



}


