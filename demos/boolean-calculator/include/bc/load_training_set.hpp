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
  thread_local std::unordered_map<bc::PromptEnum, emp::vector<bc::TestCase>> cached_grouped_set{ [](){
    const auto& cases = bc::load_training_set(); // vector<TestCase>

    std::unordered_map<bc::PromptEnum, emp::vector<bc::TestCase>> res;

    std::for_each(
      cases.begin(),
      cases.end(),
      [&res](const auto _case){
        res[_case.prompts.front().which].push_back(_case);
      }
    );

    emp_assert(
    res.size() == magic_enum::enum_count<bc::PromptEnum>() - 1, // ignore NUM
    "Missing operations in test cases.");

    return res;
  }() };

  return cached_grouped_set;

}

} // namespace bc
