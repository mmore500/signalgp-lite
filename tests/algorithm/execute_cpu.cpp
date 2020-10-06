#include <algorithm>
#include <ratio>

#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/identity.hpp"
#include "Empirical/source/tools/Random.h"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Cpu.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/program/Library.hpp"

TEST_CASE("Test execute_cpu") {

  emp::Random rand;

  sgpl::Cpu cpu;
  sgpl::Program program{ rand, 100 };

  REQUIRE( cpu.GetNumCores() == 0 );

  cpu.LaunchCore();
  REQUIRE( cpu.GetNumCores() == 1 );

  cpu.LaunchCore();
  cpu.LaunchCore();
  REQUIRE( cpu.GetNumCores() == 3 );

  sgpl::execute_cpu<sgpl::Library>( 10 * std::mega::num, cpu, program );

  REQUIRE( cpu.GetNumCores() == 3 );

  REQUIRE( std::any_of(
    std::begin( cpu ),
    std::end( cpu ),
    [](const auto& core){
      return std::any_of(
        std::begin( core.registers ),
        std::end( core.registers ),
        std::identity
      );
    }
  ) );

}
