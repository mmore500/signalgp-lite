#pragma once

#include "cereal/include/cereal/types/vector.hpp"
#include "Empirical/include/emp/base/vector.hpp"

#include "Prompt.hpp"

namespace bc {

class TestCase {

  emp::vector<bc::Prompt> prompts;

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

} // namespace bc
