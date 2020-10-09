#include <benchmark/benchmark.h>

#include "conduit/include/uitsl/debug/benchmark_utils.hpp"
#include "Empirical/source/tools/string_utils.h"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/config/Spec.hpp"

#include "sgpl/library/prefab/prefab.hpp"

#define STRINGIFY(s) #s

#define CLASSIFY(NAME) CLASSIFY_(NAME)
#define CLASSIFY_(NAME) NAME ## OpLibrary

#define FUNCTIONIFY(NAME) FUNCTIONIFY_(NAME)
#define FUNCTIONIFY_(NAME) Lite_ ## NAME

using spec_t = sgpl::Spec<sgpl:: CLASSIFY(OP_LIBRARY)>;

template<size_t NUM_AGENTS>
static void DoBench(benchmark::State& state) {

  emp::Random rand;

  sgpl::Program<spec_t> program{ rand, 100 };

  emp::vector<sgpl::Cpu<spec_t>> collection( NUM_AGENTS );
  for (auto& cpu : collection) {
    cpu.InitializeAnchors( program );
    cpu.LaunchCore();
    assert( cpu.GetNumCores() == 1 );
  }

  size_t agent{};

  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    sgpl::execute_cpu<spec_t>( 1, collection[agent], program );
    ++agent %= NUM_AGENTS;
  }

  for (const auto& cpu : collection) assert( cpu.GetNumCores() == 1 );

}

template<size_t NUM_AGENTS>
struct Setup {

  Setup() {

    auto res = benchmark::RegisterBenchmark(
      emp::to_string(
        "Lite_", STRINGIFY(OP_LIBRARY), "<", NUM_AGENTS, ">"
      ).c_str(),
      DoBench<NUM_AGENTS>
    );

    uitsl::report_confidence( res );

  }

};

Setup<1> s1;
Setup<32> s32;
Setup<1024> s1024;
Setup<32768> s32768;

static void FUNCTIONIFY(OP_LIBRARY)(benchmark::State& state) {

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
BENCHMARK(FUNCTIONIFY(OP_LIBRARY));

// Run the benchmark
BENCHMARK_MAIN();
