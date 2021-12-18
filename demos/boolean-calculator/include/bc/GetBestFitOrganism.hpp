#pragma once

#include <map>
#include <tuple>

#include "Empirical/include/emp/base/vector.hpp"
#include "Empirical/include/emp/Evolve/World.hpp"


namespace bc {

template <typename Org>
auto GetBestFitOrganism(emp::World<Org>& world) {
  // select best-fit individual
  std::multimap<double, size_t> fit_map;
  emp::vector<double> fitnesses;
  for (size_t id = 0; id < world.GetSize(); id++) {
    if (world.IsOccupied(id)) {
      const double cur_fit = world.CalcFitnessID(id);
      fit_map.insert( std::make_pair(cur_fit, id) );
      fitnesses.push_back(cur_fit);
    }
  }

  // Grab the top fitnesses and move them into the next generation.
  auto m = fit_map.rbegin();

  return std::tuple{m->first, world.GetGenomeAt(m->second), fitnesses};
}

}
