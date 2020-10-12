#pragma once

#include <algorithm>
#include <cstddef>

#include "../../../third-party/cereal/include/cereal/cereal.hpp"
#include "../../../third-party/cereal/include/cereal/types/string.hpp"
#include "../../../third-party/Empirical/source/base/array.h"
#include "../../../third-party/Empirical/source/tools/BitSet.h"
#include "../../../third-party/Empirical/source/tools/Random.h"

namespace sgpl {

template<typename Spec>
struct Instruction {

  using library_t = typename Spec::library_t;

  unsigned char op_code;

  emp::array<unsigned char, 3> args;

  emp::BitSet<32> tag;

  Instruction() = default;

  Instruction(emp::Random& rand)
  : op_code( rand.GetUInt( library_t::GetSize() ) )
  , tag( rand )
  {
    std::generate(
      std::begin( args ),
      std::end( args ),
      [&rand](){ return rand.GetUInt( Spec::num_registers ); }
    );
    emp_assert( library_t::GetSize() < 256 );
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

} // namespace sgpl
