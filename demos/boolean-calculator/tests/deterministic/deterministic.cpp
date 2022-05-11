

#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/mutate/point_mutate.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/spec/StarterConfig.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>

#include "Empirical/include/emp/base/vector.hpp"
#include "Empirical/include/emp/datastructs/hash_utils.hpp"
#include "Empirical/include/emp/tools/keyname_utils.hpp"
#include "Empirical/include/emp/Evolve/World.hpp"
#include "Empirical/include/emp/Evolve/Systematics.hpp"
#include "Empirical/include/emp/math/Random.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/library/OpLibraryCoupler.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

#include "magic_enum/include/magic_enum.hpp"

#include "bc/config.hpp"
#include "bc/load_training_set.hpp"
#include "bc/EmpWorldSerialize.hpp"
#include "bc/Organism.hpp"
#include "bc/backtrace_enable.hpp"
#include "bc/Peripheral.hpp"
#include "bc/setup.hpp"
#include "bc/TestCase.hpp"
#include "bc/ToggleRegulationOpLibrary.hpp"
#include "bc/GetBestFitOrganism.hpp"
#include "bc/GetFitFuns.hpp"

#include "bc/operations/operations.hpp"

const size_t PopulationSize = 10;
const size_t Updates = 10;

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

TEST_CASE("Test determinicity of serialization") {
  // set default starter config
  sgpl::StarterConfig cfg;

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  // declare world
  emp::World<bc::Organism<spec_t>> world_a;

  // fill world with organisms
  for (int i = 0; i < PopulationSize; i++) world_a.Inject({});

  // main evolution loop
  for (size_t t = 0; t < Updates; ++t) {
    emp::LexicaseSelect(world_a, bc::GetFitFuns<spec_t>(), PopulationSize);

    world_a.Update();
    world_a.DoMutations();
  }

  // reinitialize tlrand
  sgpl::tlrand.Reseed(1);

  // declare world
  emp::World<bc::Organism<spec_t>> world_b;

  // fill world with organisms
  for (int i = 0; i < PopulationSize; i++) world_b.Inject({});

  // main evolution loop
  for (size_t t = 0; t < Updates; ++t) {
    emp::LexicaseSelect(world_b, bc::GetFitFuns<spec_t>(), PopulationSize);

    world_b.Update();
    world_b.DoMutations();
  }

  auto serialized_a = bc::SerializeWorld(world_a);
  auto serialized_b = bc::SerializeWorld(world_a);

  REQUIRE(serialized_a == serialized_b);
}

TEST_CASE("Test determinicity of program seeding") {
  // set default starter config
  sgpl::StarterConfig cfg;

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  // declare world
  emp::World<bc::Organism<spec_t>> world_a;

  // fill world with organisms
  for (int i = 0; i < PopulationSize; i++) world_a.Inject({});

  // reinitialize tlrand
  sgpl::tlrand.Reseed(1);

  // declare world
  emp::World<bc::Organism<spec_t>> world_b;

  // fill world with organisms
  for (int i = 0; i < PopulationSize; i++) world_b.Inject({});

  auto serialized_a = bc::SerializeWorld(world_a);
  auto serialized_b = bc::SerializeWorld(world_b);

  REQUIRE(serialized_a == serialized_b);
}

TEST_CASE("Test determinicity of mutations") {
  // set default starter config
  sgpl::StarterConfig cfg;

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  // declare world
  emp::World<bc::Organism<spec_t>> world_a;

  // fill world with organisms
  for (int i = 0; i < PopulationSize; i++) world_a.Inject({});

  // main evolution loop
  for (size_t t = 0; t < Updates; ++t) {
    world_a.DoMutations();
  }

  // reinitialize tlrand
  sgpl::tlrand.Reseed(1);

  // declare world
  emp::World<bc::Organism<spec_t>> world_b;

  // fill world with organisms
  for (int i = 0; i < PopulationSize; i++) world_b.Inject({});

  // main evolution loop
  for (size_t t = 0; t < Updates; ++t) {
    world_b.DoMutations();
  }

  auto serialized_a = bc::SerializeWorld(world_a);
  auto serialized_b = bc::SerializeWorld(world_b);

  REQUIRE(serialized_a == serialized_b);
}


template <typename Spec>
auto GetFitFuns(const emp::vector<int>& indices, const emp::vector<bc::TestCase>& training_set, bool verbose = false) {
  emp::vector< std::function<double(const bc::Organism<Spec>&)> > fit_funs;

  // test first 25 cases
  for (size_t i{}; i < 25; i++) {
    const auto& case_ = training_set[ indices[i] ];

    fit_funs.push_back(
      [&case_, verbose](const bc::Organism<Spec>& org) -> double {
        return org.Evaluate(case_, verbose);
      }
    );
  }

  return fit_funs;
}

TEST_CASE("Test determinicity of selection scheme") {
  // set default starter config
  sgpl::StarterConfig cfg;

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  const emp::vector<bc::TestCase>& training_set = bc::load_training_set(); // load training set by ref

  emp::vector<int> indices(training_set.size());
  std::iota(
    indices.begin(),
    indices.end(),
    0
  );

  emp::Shuffle(sgpl::tlrand.Get(), indices);

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  // declare world
  emp::World<bc::Organism<spec_t>> world_a;

  // fill world with organisms
  for (int i = 0; i < PopulationSize; i++) world_a.Inject({});

  // main evolution loop
  for (size_t t = 0; t < Updates; ++t) {
    emp::LexicaseSelect(world_a, GetFitFuns<spec_t>(indices, training_set), PopulationSize);
    world_a.Update();
  }

  // reinitialize tlrand
  sgpl::tlrand.Reseed(1);

  // declare world
  emp::World<bc::Organism<spec_t>> world_b;

  // fill world with organisms
  for (int i = 0; i < PopulationSize; i++) world_b.Inject({});

  // main evolution loop
  for (size_t t = 0; t < Updates; ++t) {
    emp::LexicaseSelect(world_b, GetFitFuns<spec_t>(indices, training_set), PopulationSize);
    world_b.Update();
  }

  auto serialized_a = bc::SerializeWorld(world_a);
  auto serialized_b = bc::SerializeWorld(world_b);

  REQUIRE(serialized_a == serialized_b);
}
