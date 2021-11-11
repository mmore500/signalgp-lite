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
#include "include/bc/GetState.hpp"
#include "include/bc/load_training_set.hpp"
#include "include/bc/Organism.hpp"
#include "include/bc/Peripheral.hpp"
#include "include/bc/setup.hpp"
#include "include/bc/TestCase.hpp"
#include "include/bc/ToggleRegulationOpLibrary.hpp"

const size_t PopulationSize = 1000;


namespace bc {

struct SetGlobal {
  template<typename Spec>
  static void run(
      sgpl::Core<Spec>& core,
      const sgpl::Instruction<Spec>& inst,
      const sgpl::Program<Spec>&,
      typename Spec::peripheral_t& peripheral
  ) {
    const size_t a = inst.args[0];
    const size_t b = inst.args[1];

    peripheral.global_registers[a] = core.registers[b];
  }

  static std::string name() { return "SetGlobal"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& ) {
    return std::map<std::string, std::string>{};
  }
};

struct GetGlobal {
  template<typename Spec>
  static void run(
      sgpl::Core<Spec>& core,
      const sgpl::Instruction<Spec>& inst,
      const sgpl::Program<Spec>&,
      typename Spec::peripheral_t& peripheral
  ) {
    const size_t a = inst.args[0];
    const size_t b = inst.args[1];

    core.registers[a] = peripheral.global_registers[b];
  }

  static std::string name() { return "GetGlobal"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& ) {
    return std::map<std::string, std::string>{};
  }
};

struct SetAllGlobal {
  template<typename Spec>
  static void run(
      sgpl::Core<Spec>& core,
      const sgpl::Instruction<Spec>& inst,
      const sgpl::Program<Spec>&,
      typename Spec::peripheral_t& peripheral
  ) {
    peripheral.global_registers = core.registers;
  }

  static std::string name() { return "SetAllGlobal"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& ) {
    return std::map<std::string, std::string>{};
  }
};

struct GetAllGlobal {
  template<typename Spec>
  static void run(
      sgpl::Core<Spec>& core,
      const sgpl::Instruction<Spec>& inst,
      const sgpl::Program<Spec>&,
      typename Spec::peripheral_t& peripheral
  ) {
    core.registers = peripheral.global_registers;
  }

  static std::string name() { return "GetAllGlobal"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& ) {
    return std::map<std::string, std::string>{};
  }
};
} // namespace bc

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

namespace bc {
  auto& load_grouped_training_set() {
    thread_local std::unordered_map<bc::PromptEnum, emp::vector<bc::TestCase>> grouped_set;

    const auto& cases = bc::load_training_set(); // vector<TestCase>

    std::for_each(
      cases.begin(),
      cases.end(),
      [](const auto _case){
        grouped_set[_case.prompts.front().which].push_back(_case);
      }
    );

    return grouped_set;
  }
};


auto GetFitFuns(bool verbose = false) {
  emp::vector< std::function<double(const bc::Organism<spec_t>&)> > fit_funs;

  // emp_assert(
  //     grouped_set.size() == magic_enum::enum_count<bc::PromptEnum>() - 1, // ignore NUM
  //     "Missing operations in test cases.");

  for (auto& [type, cases] : grouped_set) {
    // shuffle the prompts
    emp::Shuffle(sgpl::tlrand.Get(), cases);

    // &x=x due to clang's standards stickling on capturing structured bindings
    // see https://burnicki.pl/en/2021/04/19/capture-structured-bindings.html
    fit_funs.push_back(
      [&cases=cases, verbose](const bc::Organism<spec_t>& org) -> double {
        return org.Evaluate(cases.front(), verbose);
      }
    );
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
    //ea_world.DoMutations();
    emp::LexicaseSelect(ea_world, GetFitFuns(), PopulationSize);
    ea_world.Update();

    //
    auto best_fit = get_best_fit_individual();
    best_fit.GetFitness(true);

    // for (auto func : GetFitFuns(true)) {
    //   func(best_fit);
    // }

    // check for early exit
    const double max_fitness = get_max_fitness();
    if (max_fitness >= bc::config.THRESHOLD_FITNESS()) break;
  }

  print_fitness();
}
