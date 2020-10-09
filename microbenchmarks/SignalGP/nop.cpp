#include <benchmark/benchmark.h>

#include "conduit/include/uitsl/debug/benchmark_utils.hpp"
#include "Empirical/source/tools/string_utils.h"

#include "_BenchHolder.hpp"
#include "_Inst_Loop.hpp"
#include "_SignalGP.hpp"


inst_lib_t inst_lib;
event_lib_t event_lib;
program_t program;

struct SetupA {

  SetupA() {

    inst_lib.AddInst("Nop", sgp::inst_impl::Inst_Nop<signalgp_t, inst_t>, "");

    emp::Random rand;

    program = sgp::GenRandLinearFunctionsProgram<signalgp_t, 32>(
      rand,
      inst_lib,
      {1, 1}, // num functions
      1, // num func tags
      {100, 100}, // num instructions
      1, // num inst tags
      3, // num inst args
      {0, 5}
    );

    inst_lib.AddInst(
      "Loop",
      Inst_Loop<signalgp_t, inst_t>,
      "",
      {inst_prop_t::BLOCK_DEF}
    );
    inst_lib.AddInst(
      "Close",
      sgp::inst_impl::Inst_Close<signalgp_t, inst_t>,
      "",
      {inst_prop_t::BLOCK_CLOSE}
    );

    program[0][0].SetID( inst_lib.GetID("Loop") );
    program[0][99].SetID( inst_lib.GetID("Close") );

  }

} setup_a;


BenchHolder<1> bench1{ program, inst_lib, event_lib };
BenchHolder<32> bench32{ program, inst_lib, event_lib };
BenchHolder<1024> bench1024{ program, inst_lib, event_lib };
BenchHolder<32768> bench32768{ program, inst_lib, event_lib };

template<size_t NUM_AGENTS>
void Register(BenchHolder<NUM_AGENTS>& holder) {
  auto res = benchmark::RegisterBenchmark(
    emp::to_string(
      "Lite_Arithmetic<", NUM_AGENTS, ">"
    ).c_str(),
    [&](benchmark::State& state){ holder.Run(state); }
  );

  uitsl::report_confidence( res );

}


struct SetupB {

  SetupB() {
    Register<1>( bench1 );
    Register<32>( bench32 );
    Register<1024>( bench1024);
    Register<32768>( bench32768 );
  }

} setup_b;

// Run the benchmark
BENCHMARK_MAIN();
