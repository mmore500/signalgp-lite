#pragma once

#include "../third-party/cereal/include/cereal/cereal.hpp"
#include "../third-party/cereal/include/cereal/types/optional.hpp"
#include "../third-party/Empirical/include/emp/base/optional.hpp"

#include "PromptEnum.hpp"

namespace sgpl::demos {

class Prompt {

  sgpl::demos::PromptEnum which;

  emp::optional<uint32_t> val;

public:

  // binary input/output
  template<typename Archive>
  void serialize( Archive& archive ) {
    archive(
      CEREAL_NVP( which ),
      CEREAL_NVP( val )
    );
  }

};

// adapted from https://stackoverflow.com/a/40006041
namespace cereal {

  template <class Archive> inline
  std::string save_minimal(
    Archive const &, sgpl::demos::PromptEnum const & t
  ) {
    return std::string(
      magic_enum::enum_name(t)
    );
  }

  template <class Archive> inline
  void load_minimal(
    Archive const &, sgpl::demos::PromptEnum & t, std::string const & value
  ) {
    t = *magic_enum::enum_cast<sgpl::demos::PromptEnum>( value );
  }

} // namespace cereal

};
