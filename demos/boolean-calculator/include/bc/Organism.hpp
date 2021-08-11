#pragma once

#include <algorithm>

#include "Empirical/include/emp/base/vector.hpp"

#include "sgpl/program/Program.hpp"
#include "sgpl/utility/CountingIterator.hpp"

#include "config.hpp"
#include "load_training_set.hpp"
#include "Peripheral.hpp"
#include "PromptEnum.hpp"
#include "TestCase.hpp"

namespace bc {

template<typename Spec>
struct Organism {

  using program_t = sgpl::Program<Spec>;
  using tag_t = typename Spec::tag_t;

  program_t program{256};

  bool Evaluate(const bc::TestCase& case_) const {

    bc::Peripheral peripheral;
    sgpl::Cpu<Spec> cpu;

    cpu.InitializeAnchors(program);

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
        auto& reg = cpu.GetFreshestCore().registers.front();
        reg = std::bit_cast<float>(*prompt.val);
      }

      // execute up to 128 instructions
      sgpl::execute_cpu<Spec>(128, cpu, program, peripheral);

    }

    return peripheral.output == case_.response;

  }

  double GetFitness() const {

    const size_t num_tests = 20;
    const size_t num_passed = std::accumulate(
      sgpl::CountingIterator{},
      sgpl::CountingIterator{num_tests},
      size_t{},
      [this](const auto& running_sum, const auto&){
        const auto& cases = load_training_set();
        const size_t case_idx = sgpl::tlrand.Get().GetUInt( cases.size() );
        const auto& case_ = cases[ case_idx ];
        return running_sum + Evaluate( case_ );
      }
    );

    return num_passed / static_cast<double>(num_tests);

  }

  bool DoMutations(emp::Random&) {
    program.ApplyMutations(bc::config);
    return true;
  }

};

} // namespace bc
