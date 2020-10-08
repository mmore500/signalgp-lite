#include <benchmark/benchmark.h>

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/library/prefab/NopOpLibrary.hpp"

using spec_t = sgpl::Spec<sgpl::NopOpLibrary>;

static void Lite_Nop(benchmark::State& state) {

  emp::Random rand;

  sgpl::Cpu<spec_t> cpu;
  sgpl::Program<spec_t> program{ rand, 100 };
  cpu.InitializeAnchors( program );

  cpu.LaunchCore();

  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    sgpl::execute_cpu<spec_t>( 1, cpu, program );
  }
}
// Register the function as a benchmark
BENCHMARK(Lite_Nop);
// Run the benchmark
BENCHMARK_MAIN();
