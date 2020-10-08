#include <benchmark/benchmark.h>

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/library/prefab/ArithmeticOpLibrary.hpp"

static void BM_Arithmetic(benchmark::State& state) {

  emp::Random rand;

  sgpl::Cpu<sgpl::ArithmeticOpLibrary> cpu;
  sgpl::Program<sgpl::ArithmeticOpLibrary> program{ rand, 100 };
  cpu.InitializeAnchors( program );

  cpu.LaunchCore();

  assert( cpu.GetNumCores() == 1 );

  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    sgpl::execute_cpu<sgpl::ArithmeticOpLibrary>( 1, cpu, program );
  }

  assert( cpu.GetNumCores() == 1 );

}
// Register the function as a benchmark
BENCHMARK(BM_Arithmetic);
// Run the benchmark
BENCHMARK_MAIN();
