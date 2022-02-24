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
#include "magic_enum/include/magic_enum.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/library/OpLibraryCoupler.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

#include "include/bc/config.hpp"
#include "include/bc/load_training_set.hpp"
#include "include/bc/EmpWorldSerialize.hpp"
#include "include/bc/Organism.hpp"
#include "include/bc/backtrace_enable.hpp"
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

  using mut_count_t = std::unordered_map<std::string, int>;
  using data_t = emp::datastruct::mut_landscape_info<emp::vector<double>>;
  using org_t = bc::Organism<spec_t>;
  using gene_systematics_t = emp::Systematics<org_t, org_t::program_t, data_t>;
  // using phen_systematics_t = emp::Systematics<org_t, emp::vector<double>, data_t>;

  auto gene_fun = [](const org_t& org) {
    return org.program;
  };

  mut_count_t last_mutation;
  emp::Ptr<gene_systematics_t> gene_sys;
  gene_sys.New(gene_fun, true,true,true);

  emp::World<bc::Organism<spec_t>> ea_world;
  ea_world.SetPopStruct_Mixed(true);
  ea_world.AddSystematics(gene_sys);

  // setup logging
  if (bc::config.LOGGING()) {
    auto& fitness_file = ea_world.SetupFitnessFile(
      emp::keyname::pack({
        {"a", "fitness"},
        {"point_rate", emp::to_string(bc::config.SGPL_POINTMUTATE_BITFLIP_RATE())},
        {"sequence_rate", emp::to_string(bc::config.SGPL_SEQMUTATE_INST_INDEL_RATE())},
        {"replicate", emp::to_string(bc::config.REPLICATE())},
        {"ext", ".csv"}
      }),
      false
    );

    fitness_file.AddFun(
      [](){ return uitsl::get_proc_instance_uuid(); },
      "exec_instance_uuid",
      "exec_instance_uuid"
    );

    fitness_file.AddFun(
      [](){ return bc::get_git_revision(); },
      "git_revision",
      "git_revision"
    );

    fitness_file.PrintHeaderKeys();

    auto& systematics_file = ea_world.SetupSystematicsFile(
      0,
      emp::keyname::pack({
        {"a", "systematics"},
        {"point_rate", emp::to_string(bc::config.SGPL_POINTMUTATE_BITFLIP_RATE())},
        {"sequence_rate", emp::to_string(bc::config.SGPL_SEQMUTATE_INST_INDEL_RATE())},
        {"replicate", emp::to_string(bc::config.REPLICATE())},
        {"ext", ".csv"}
      }),
      false
    );

    systematics_file.AddFun(
      [](){ return uitsl::get_proc_instance_uuid(); },
      "exec_instance_uuid",
      "exec_instance_uuid"
    );

    systematics_file.AddFun(
      [](){ return bc::get_git_revision(); },
      "git_revision",
      "git_revision"
    );

    systematics_file.PrintHeaderKeys();

  }

  // fill world with organisms
  for (int i = 0; i < PopulationSize; i++) ea_world.Inject({});

  // main evolution loop
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

    ea_world.Update();
    ea_world.DoMutations();
  }

  // save genome
  std::ofstream os(
    emp::keyname::pack({
      {"a", "genome"},
      {"point_rate", emp::to_string(bc::config.SGPL_POINTMUTATE_BITFLIP_RATE())},
      {"sequence_rate", emp::to_string(bc::config.SGPL_SEQMUTATE_INST_INDEL_RATE())},
      {"replicate", emp::to_string(bc::config.REPLICATE())},
      {"ext", ".json"}
    })
  );
  cereal::JSONOutputArchive archive( os );

  archive( bc::SerializeWorld(ea_world) );

  // save genome metadata
  emp::DataFile metadata_file(
    emp::keyname::pack({
      {"a", "genome"},
      {"point_rate", emp::to_string(bc::config.SGPL_POINTMUTATE_BITFLIP_RATE())},
      {"sequence_rate", emp::to_string(bc::config.SGPL_SEQMUTATE_INST_INDEL_RATE())},
      {"replicate", emp::to_string(bc::config.REPLICATE())},
      {"ext", ".json.meta"}
    })
  );

  metadata_file.AddFun(
    [](){ return uitsl::get_proc_instance_uuid(); },
    "exec_instance_uuid",
    "exec_instance_uuid"
  );

  metadata_file.AddFun(
    [](){ return bc::get_git_revision(); },
    "git_revision",
    "git_revision"
  );

  metadata_file.PrintHeaderKeys();
  metadata_file.Update();

}
