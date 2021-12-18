#pragma once

#include "cereal/include/cereal/archives/json.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "config.hpp"
#include "TestCase.hpp"

namespace bc {

const emp::vector<bc::TestCase>& load_training_set() {

  thread_local emp::vector<bc::TestCase> cached{ [](){

    emp::vector<bc::TestCase> res;

    std::ifstream ifs{
      bc::config.TRAINING_SET_FILENAME()
    };
    cereal::JSONInputArchive archive{ ifs };

    archive( res );

    return res;

  }() };

  return cached;

}

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

} // namespace bc
