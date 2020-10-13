#pragma once

#include <algorithm>
#include <cstddef>
#include <tuple>

#include "../../../third-party/cereal/include/cereal/archives/json.hpp"
#include "../../../third-party/cereal/include/cereal/cereal.hpp"
#include "../../../third-party/cereal/include/cereal/types/array.hpp"
#include "../../../third-party/cereal/include/cereal/types/string.hpp"
#include "../../../third-party/Empirical/source/base/array.h"
#include "../../../third-party/Empirical/source/tools/BitSet.h"
#include "../../../third-party/Empirical/source/tools/Random.h"

#include "OpCodeRectifier.hpp"

namespace sgpl {

template<typename Spec>
struct Instruction {

  using library_t = typename Spec::library_t;
  using rectifier_t = sgpl::OpCodeRectifier<library_t>;

  unsigned char op_code;

  std::array<unsigned char, 3> args;

  emp::BitSet<32> tag;

  void RectifyArgs() { for (auto& arg : args) arg %= Spec::num_registers; }

  void RectifyOpCode(const rectifier_t& r) { op_code = r.Rectify(op_code); }

  void Rectify(const rectifier_t& r) { RectifyArgs(); RectifyOpCode(r); }

  bool operator==(const Instruction& other) const {
    return (
      std::tuple{ op_code, args, tag }
      == std::tuple{ other.op_code, other.args, other.tag }
    );
  }

  // human-readable output
  template<
    typename Archive,
    cereal::traits::EnableIf<cereal::traits::is_text_archive<Archive>::value>
    = cereal::traits::sfinae
  >
  void save( Archive& archive ) const {
    std::stringstream ss;
    tag.Print( ss );

    archive(
      cereal::make_nvp("operation", library_t::GetOpName(op_code) ),
      CEREAL_NVP( args ),
      cereal::make_nvp("bitstring", ss.str() )
    );

  }

  // human-readable input
  template<
    typename Archive,
    cereal::traits::EnableIf<cereal::traits::is_text_archive<Archive>::value>
    = cereal::traits::sfinae
  >
  void load( Archive& archive ) {
    std::string op_name;
    std::string bitstring;

    archive(
      cereal::make_nvp( "operation", op_name ),
      CEREAL_NVP( args ),
      cereal::make_nvp( "bitstring", bitstring )
    );

    op_code = library_t::GetOpCode( op_name );
    tag = emp::BitSet<32>( bitstring );

  }

  // binary input/output
  template<
    typename Archive,
    cereal::traits::DisableIf<cereal::traits::is_text_archive<Archive>::value>
    = cereal::traits::sfinae
  >
  void serialize( Archive& archive ) {
    archive(
      CEREAL_NVP( op_code ),
      CEREAL_NVP( args ),
      CEREAL_NVP( tag )
    );
  }

};

template<typename Spec>
std::ostream& operator<<(std::ostream& os, const Instruction<Spec>& inst) {
  cereal::JSONOutputArchive archive{ os };
  archive( inst );
  return os;
}

} // namespace sgpl
