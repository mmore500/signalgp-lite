#pragma once

#include <algorithm>

#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/program/Program.hpp"
#include "sgpl/utility/CountingIterator.hpp"

#include "config.hpp"
#include "load_testing_set.hpp"
#include "load_training_set.hpp"
#include "Peripheral.hpp"
#include "PromptEnum.hpp"
#include "TestCase.hpp"

#include "conduit/include/uitsl/polyfill/filesystem.hpp"

namespace bc {

template<typename Spec>
struct Organism {

  using program_t = sgpl::Program<Spec>;
  using tag_t = typename Spec::tag_t;

  program_t program{std::filesystem::path{
    "nand_program.json"
  }};

  bool Evaluate(const bc::TestCase& case_, bool verbose = false) const {

    bc::Peripheral peripheral;
    sgpl::Cpu<Spec> cpu;

    cpu.InitializeAnchors(program);

    std::string case_name;

    const static emp::vector<tag_t> prompt_tags = [](){
      emp::vector<tag_t> res;
      std::generate_n(
        std::back_inserter( res ),
        magic_enum::enum_count<bc::PromptEnum>(),
        [](){ return tag_t( sgpl::tlrand.Get() ); }
      );
      return res;
    }();

    for (const auto& prompt : case_.prompts) {
      const auto prompt_idx = magic_enum::enum_integer( prompt.which );
      const auto& prompt_tag = prompt_tags[ prompt_idx ];

      const auto did_launch = cpu.TryLaunchCore( prompt_tag );

      if ( did_launch && prompt.val.has_value() ) {
        // peripheral.input = std::bit_cast<float>(*prompt.val);
        peripheral.input = static_cast<float>(*prompt.val);
        std::cout << "input: " << *prompt.val << ", " << peripheral.input << std::endl;
      } else {
        // is an operation
        case_name = magic_enum::enum_name( prompt.which );
        std::cout << case_name << ": " << case_.response << ", " << peripheral.output <<
        ". " << static_cast<int>(peripheral.output == case_.response) << std::endl;

      }

      // execute up to 128 instructions
      sgpl::execute_cpu<Spec>(128, cpu, program, peripheral);

    }
    if (verbose) std::cout << case_name << ": " << static_cast<int>(peripheral.output == case_.response) << std::endl;

    return peripheral.output == case_.response;

  }
  double GetTrainingFitness(bool verbose = false) const {
    const size_t num_tests = 1;
    const size_t num_passed = std::accumulate(
      sgpl::CountingIterator{},
      sgpl::CountingIterator{num_tests},
      size_t{},
      [this, verbose](const auto& running_sum, const auto&){
        const auto& cases = load_training_set();
        const size_t case_idx = sgpl::tlrand.Get().GetUInt( cases.size() );
        const auto& case_ = cases[ case_idx ];
        return running_sum + Evaluate( case_, verbose );
      }
    );

    return num_passed / static_cast<double>(num_tests);
  }
  double GetTestingFitness() const {
    const auto& cases = load_testing_set();
    const size_t num_passed = std::accumulate(
      cases.begin(),
      cases.end(),
      size_t{},
      [this](const auto& running_sum, const auto& test_case){
        return running_sum + Evaluate( test_case );
      }
    );

    return num_passed / static_cast<double>(cases.size());
  }

  double GetFitness(bool verbose = false) const { return GetTrainingFitness(verbose); }

  bool DoMutations(emp::Random&) {
    program.ApplyMutations(bc::config);
    return true;
  }

};

} // namespace bc
