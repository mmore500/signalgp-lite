

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

TEST_CASE("Test Organism Evaluate determinicity") {
  // set default starter config
  sgpl::StarterConfig cfg;

  // load training set
  const emp::vector<bc::TestCase>& training_set = bc::load_training_set(); // load training set by ref

  // declare organism
  bc::Organism<spec_t> org;

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  std::vector<size_t> results_a;
  std::vector<size_t> results_b;

  for (const auto& _case : training_set) {
    results_a.push_back(org.Evaluate(_case));
  }

  // reinitialize tlrand
  sgpl::tlrand.Reseed(1);

  for (const auto& _case : training_set) {
    results_b.push_back(org.Evaluate(_case));
  }

  REQUIRE(results_a == results_b);

}

