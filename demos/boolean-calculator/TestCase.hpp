#pragma once

#include "../third-party/cereal/include/cereal/types/vector.hpp"
#include "../third-party/Empirical/include/emp/base/vector.hpp"

#include "Prompt.hpp"

namespace sgpl::demos {

class TestCase {

  emp::vector<sgpl::demos::Prompt> prompts;

  uint32_t response;

public:

  // binary input/output
  template<typename Archive>
  void serialize( Archive& archive ) {
    archive(
      CEREAL_NVP( prompts ),
      CEREAL_NVP( response )
    );
  }

};

} // namespace sgpl::demos
