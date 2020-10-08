#include <benchmark/benchmark.h>

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/library/prefab/NopOpLibrary.hpp"

static void BM_Nop(benchmark::State& state) {

  emp::Random rand;

  sgpl::Cpu<sgpl::NopOpLibrary> cpu;
  sgpl::Program<sgpl::NopOpLibrary> program{ rand, 100 };
  cpu.InitializeAnchors( program );

  cpu.LaunchCore();

  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    sgpl::execute_cpu<sgpl::NopOpLibrary>( 1, cpu, program );
  }
}
// Register the function as a benchmark
BENCHMARK(BM_Nop);
// Run the benchmark
BENCHMARK_MAIN();
