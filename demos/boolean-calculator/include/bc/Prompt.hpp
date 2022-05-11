#pragma once

#include "cereal/include/cereal/cereal.hpp"
#include "cereal/include/cereal/types/optional.hpp"
#include "Empirical/include/emp/base/optional.hpp"

#include "PromptEnum.hpp"

namespace bc {

struct Prompt {

  bc::PromptEnum which;

  emp::optional<uint32_t> val;

  // binary input/output
  template<typename Archive>
  void serialize( Archive& archive ) {
    archive(
      CEREAL_NVP( which ),
      CEREAL_NVP( val )
    );
  }

};

} // namespace bc
