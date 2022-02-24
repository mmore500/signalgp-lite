#pragma once

#include "conduit/include/uitsl/utility/get_proc_instance_uuid.hpp"
#include "conduit/include/uitsl/utility/exec_utils.hpp"

#include "Empirical/include/emp/config/ArgManager.hpp"

#include "sgpl/utility/ThreadLocalRandom.hpp"

#include "config.hpp"
#include "get_git_revision.hpp"

namespace bc {

void setup(int argc, char* argv[]) {

  // make argmanager specs from config
  auto specs = emp::ArgManager::make_builtin_specs(&config);

  emp::ArgManager arg_manager{argc, argv, specs};

  arg_manager.UseCallbacks();

  // set proc UUID
  bc::config.Set(
    "EXEC_INSTANCE_UUID",
    emp::to_string(uitsl::get_proc_instance_uuid()),
    "Unique process identifier"
  );

  // set git revision
  bc::config.Set(
    "GIT_REVISION",
    emp::to_string(bc::get_git_revision()),
    "Hash of last git commit"
  );

  // print config
  bc::config.Write(std::cout);

  // save config as csv
  bc::config.WriteCSV(
    emp::keyname::pack({
      {"a", "config"},
      {"point_rate", emp::to_string(bc::config.SGPL_POINTMUTATE_BITFLIP_RATE())},
      {"sequence_rate", emp::to_string(bc::config.SGPL_SEQMUTATE_INST_INDEL_RATE())},
      {"replicate", emp::to_string(bc::config.REPLICATE())},
      {"ext", ".csv"}
    })
  );

  // reseed random number generator
  sgpl::tlrand.Reseed(config.SEED());


}

} // namespace bc
