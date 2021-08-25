#pragma once

#include "Empirical/include/emp/config/ArgManager.hpp"

#include "sgpl/utility/ThreadLocalRandom.hpp"

#include "config.hpp"

namespace bc {

void setup(int argc, char* argv[]) {

  // make argmanager specs from config
  auto specs = emp::ArgManager::make_builtin_specs(&config);

  emp::ArgManager arg_manager{argc, argv, specs};

  arg_manager.UseCallbacks();

  // print config
  bc::config.Write(std::cout);

  // reseed random number generator
  sgpl::tlrand.Reseed(config.SEED());


}

} // namespace bc