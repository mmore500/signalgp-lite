#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>

#include "Empirical/include/emp/base/vector.hpp"
#include "Empirical/include/emp/datastructs/hash_utils.hpp"
#include "Empirical/include/emp/Evolve/World.hpp"
#include "Empirical/include/emp/math/Random.hpp"
#include "magic_enum/include/magic_enum.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/library/OpLibraryCoupler.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

#include "include/bc/config.hpp"
#include "include/bc/load_training_set.hpp"
#include "include/bc/Organism.hpp"
#include "include/bc/Peripheral.hpp"
#include "include/bc/setup.hpp"
#include "include/bc/TestCase.hpp"
#include "include/bc/ToggleRegulationOpLibrary.hpp"
#include "include/bc/GetBestFitOrganism.hpp"
#include "include/bc/GetFitFuns.hpp"

#include "include/bc/operations/operations.hpp"

const size_t PopulationSize = 1000;

using library_t = sgpl::OpLibraryCoupler<
  bc::ToggleRegulationOpLibrary,
  bc::GetInput,
  bc::SetOutput,
  bc::GetGlobal,
  bc::SetGlobal,
  bc::GetAllGlobal,
  bc::SetAllGlobal
>;

// TODO: override spec and change line 34 to ratio<1,2>
// using spec_t = sgpl::Spec<library_t, bc::Peripheral>;
struct spec_t : public sgpl::Spec<library_t, bc::Peripheral> {
  //static constexpr inline size_t switch_steps{ 1 }; // eslint-disable-line no-eval
};

using tag_t = spec_t::tag_t;


int main(int argc, char* argv[]) {

  bc::setup(argc, argv);

  emp::World<bc::Organism<spec_t>> ea_world;
  ea_world.SetPopStruct_Mixed(true);

  if (bc::config.LOGGING()) ea_world.SetupFitnessFile(
      emp::to_string(bc::config.LOGGING_FILENAME(), ".csv")
  );

  for (int i = 0; i < PopulationSize; i++) ea_world.Inject({});

  for (size_t t = 0; t < bc::config.UPDATES(); ++t) {
    std::cout << "Update " << t << std::endl;

    auto [best_fit, best_org, fitnesses] = bc::GetBestFitOrganism(ea_world);

    std::cout << "Best fitness: " << best_fit << std::endl;

    // test for training set
    if (best_fit == 1.0) {
      const double training_fitness = best_org.GetTestingFitness();
      std::cout << "Training Fitness of Best-Fit Organism: " << training_fitness << std::endl;
    }

    for (auto org : fitnesses) std::cout << org << " ";
    std::cout << std::endl;


    emp::LexicaseSelect(ea_world, bc::GetFitFuns<spec_t>(), PopulationSize);
    // emp::EliteSelect(ea_world, 1, 1);
    // emp::TournamentSelect(ea_world, 7, PopulationSize - 1);

    // best_org.GetFitness(true);

/**
    // Reliability test
    bool reliable = std::all_of(
      sgpl::CountingIterator{},
      sgpl::CountingIterator{ea_world.size()},
      [&ea_world](const size_t id){
        return ea_world.CalcFitnessID(id) == ea_world.CalcFitnessID(id);
      }
    );

    std::cout << std::boolalpha;
    std::cout << "Reliable? " << reliable << std::endl;
**/
    ea_world.Update();
    ea_world.DoMutations();

  }

}
