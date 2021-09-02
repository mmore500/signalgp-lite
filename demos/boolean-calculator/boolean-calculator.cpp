#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>

#include "Empirical/include/emp/base/vector.hpp"
#include "Empirical/include/emp/datastructs/hash_utils.hpp"
#include "Empirical/include/emp/Evolve/World.hpp"
#include "Empirical/include/emp/math/Random.hpp"


#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/library/OpLibraryCoupler.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

#include "include/bc/config.hpp"
#include "include/bc/GetState.hpp"
#include "include/bc/Organism.hpp"
#include "include/bc/load_training_set.hpp"
#include "include/bc/Peripheral.hpp"
#include "include/bc/SetState.hpp"
#include "include/bc/setup.hpp"
#include "include/bc/TestCase.hpp"
#include "include/bc/ToggleRegulationOpLibrary.hpp"

const size_t PopulationSize = 1000;

using library_t = sgpl::OpLibraryCoupler<
  bc::ToggleRegulationOpLibrary,
  bc::GetState,
  bc::SetState
>;

// TODO: override spec and change line 34 to ratio<1,2>
using spec_t = sgpl::Spec<library_t, bc::Peripheral>;

using tag_t = spec_t::tag_t;


auto GetFitFuns() {
    emp::vector< std::function<double(const bc::Organism&)> > fit_funs;

    const auto& cases = bc::load_training_set();

    for (const auto prompt : bc::prompts) {
      // find test_case that matches prompt, randomly
      while (true) {
        const size_t case_idx = sgpl::tlrand.Get().GetUInt( cases.size() );
        const auto _case = cases[case_idx];
        if (_case.prompts)

      }


    }



    return fit_funs;
}

int main(int argc, char* argv[]) {

  bc::setup(argc, argv);

  emp::World<bc::Organism<spec_t>> ea_world;
  ea_world.SetPopStruct_Mixed(true);

  if (bc::config.LOGGING()) ea_world.SetupFitnessFile(
      emp::to_string(bc::config.LOGGING_FILENAME(), ".csv")
  );

  for (int i = 0; i < PopulationSize; i++) ea_world.Inject({});

  auto get_max_fitness = [&ea_world]() -> double {
    double max_fitness = 0;
    for (size_t i = 0; i < ea_world.GetSize(); i++) max_fitness = std::max(ea_world[i].GetFitness(), max_fitness);
    return max_fitness;
  };

  auto get_best_fit_individual = [&ea_world](){
    // select best-fit individual
    std::multimap<double, size_t> fit_map;
    for (size_t id = 0; id < ea_world.GetSize(); id++) {
      if (ea_world.IsOccupied(id)) {
        const double cur_fit = ea_world.CalcFitnessID(id);
        fit_map.insert( std::make_pair(cur_fit, id) );
      }
    }

    // Grab the top fitnesses and move them into the next generation.
    auto m = fit_map.rbegin();

    const size_t repro_id = m->second;
    return ea_world.GetGenomeAt(repro_id);
  };

  auto print_fitness = [&ea_world, get_best_fit_individual](const size_t time = -1){
    // if (time != -1) std::cout << "Update: " << time << std::endl;
    // for (size_t i = 0; i < ea_world.GetSize(); i++) std::cout << ea_world[i].GetFitness() << " ";
    // std::cout << std::endl;
    std::cout << "Best fitness: " << get_best_fit_individual().GetFitness() << std::endl;
    std::cout << std::endl;
  };

  for (size_t t = 0; t < bc::config.UPDATES(); ++t) {
    // loop normally
    print_fitness(t);
    ea_world.DoMutations();
    emp::LexicaseSelect(ea_world, GetFitFuns(), PopulationSize);
    ea_world.Update();

    // check for early exit
    const double max_fitness = get_max_fitness();
    if (max_fitness >= bc::config.THRESHOLD_FITNESS()) break;
  }

  print_fitness();

}
