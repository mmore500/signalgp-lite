#pragma once

#include "conduit/include/uitsl/utility/get_proc_instance_uuid.hpp"
#include "conduit/include/uitsl/utility/exec_utils.hpp"

#include "Empirical/include/emp/config/ArgManager.hpp"

#include "sgpl/utility/ThreadLocalRandom.hpp"

#include "config.hpp"

namespace bc {

void setup(int argc, char* argv[]) {

  // make argmanager specs from config
  auto specs = emp::ArgManager::make_builtin_specs(&config);

  emp::ArgManager arg_manager{argc, argv, specs};

  arg_manager.UseCallbacks();

  // set proc UUID
  bc::config.Set(
    "UUID",
    emp::to_string(uitsl::get_proc_instance_uuid()),
    "Unique process identifier"
  );

  // set git revision
  bc::config.Set(
    "COMMIT_HASH",
    uitsl::exec("git rev-parse HEAD"),
    "Hash of last git commit"
  );

  // print config
  bc::config.Write(std::cout);

  // save config as csv
  bc::config.WriteCSV(
    emp::keyname::pack({
      {"a", "genome"},
      {"point_rate", emp::to_string(bc::config.SGPL_POINTMUTATE_BITFLIP_RATE())},
      {"sequence_rate", emp::to_string(bc::config.SGPL_SEQMUTATE_INST_INDEL_RATE())},
      {"replicate", emp::to_string(bc::config.REPLICATE())},
      {"exec_instance_uuid", emp::to_string(uitsl::get_proc_instance_uuid())},
      {"ext", ".csv"}
    })
  );

  // reseed random number generator
  sgpl::tlrand.Reseed(config.SEED());


}

} // namespace bc
