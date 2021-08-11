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

} // namespace bc 
