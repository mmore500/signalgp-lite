#include <fstream>

#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "cereal/include/cereal/archives/binary.hpp"
#include "cereal/include/cereal/archives/json.hpp"
#include "Empirical/source/tools/Random.h"

#include "sgpl/config/Spec.hpp"
#include "sgpl/program/Program.hpp"

using spec_t = sgpl::Spec<>;

TEST_CASE("Test Program") {

  emp::Random rand;

  // TODO flesh out stub test
  sgpl::Program<spec_t> program{
    rand,
    100
  };

}

template<typename InArchive, typename OutArchive>
void DoSerializationTest(const std::string& filename) {

  emp::Random rand;

  sgpl::Program<spec_t> original{
    rand,
    100
  };

  std::ofstream os(filename);

  { OutArchive archive( os ); archive( original ); }

  os.close();

  std::ifstream is(filename);

  sgpl::Program<spec_t> reconstituted;

  { InArchive archive( is ); archive( reconstituted ); }

  REQUIRE( reconstituted == original );

  os.close();
}

TEST_CASE("Test Program Binary Serialization") {

  DoSerializationTest<cereal::BinaryInputArchive, cereal::BinaryOutputArchive>(
    "program.bin"
  );

}


TEST_CASE("Test Program Text Serialization") {

  DoSerializationTest<cereal::JSONInputArchive, cereal::JSONOutputArchive>(
    "program.json"
  );

}
