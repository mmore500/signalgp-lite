#include <benchmark/benchmark.h>

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/config/Spec.hpp"
#include "sgpl/library/prefab/ArithmeticOpLibrary.hpp"

using spec_t = sgpl::Spec<sgpl::ArithmeticOpLibrary>;

static void Lite_Arithmetic(benchmark::State& state) {

  emp::Random rand;

  sgpl::Cpu<spec_t> cpu;
  sgpl::Program<spec_t> program{ rand, 100 };
  cpu.InitializeAnchors( program );

  cpu.LaunchCore();

  assert( cpu.GetNumCores() == 1 );

  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    sgpl::execute_cpu<spec_t>( 1, cpu, program );
  }

  assert( cpu.GetNumCores() == 1 );

}
// Register the function as a benchmark
BENCHMARK(Lite_Arithmetic);
// Run the benchmark
BENCHMARK_MAIN();
