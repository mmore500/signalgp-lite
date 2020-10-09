#include <benchmark/benchmark.h>

#include "conduit/include/uitsl/debug/benchmark_utils.hpp"
#include "Empirical/source/tools/string_utils.h"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/config/Spec.hpp"

#define STRINGIFY(s) STRINGIFY_(s)
#define STRINGIFY_(s) #s

#define CLASSIFY(NAME) CLASSIFY_(NAME)
#define CLASSIFY_(NAME) NAME ## OpLibrary

#define FUNCTIONIFY(NAME) FUNCTIONIFY_(NAME)
#define FUNCTIONIFY_(NAME) Lite_ ## NAME

template<size_t NUM_AGENTS>
static void DoBench(benchmark::State& state) {

  emp::Random rand;

  sgpl::Program<spec_t> program{ rand, 100 };

  emp::vector<sgpl::Cpu<spec_t>> collection( NUM_AGENTS );
  for (auto& cpu : collection) {
    cpu.InitializeAnchors( program );
    cpu.LaunchCore();
    assert( cpu.GetNumCores() );
  }

  size_t agent{};

  emp::vector< emp::BitSet<32> > tags;
  std::generate_n(
    std::back_inserter(tags),
    20,
    [&]{ return emp::BitSet<32>(rand); }
  );
  size_t tag{};

  // Perform setup here
  for (auto _ : state) {

    auto& cpu = collection[agent];

    // This code gets timed
    if constexpr (fill_cores) {
      while ( cpu.GetNumFreeCores() ) {
        cpu.LaunchCore( tags[tag] );
        ++tag %= 20;
      }
      // do *at least* sixteen cycles
      sgpl::execute_cpu<spec_t>( 16, cpu, program );
    } else {
      sgpl::execute_cpu<spec_t>( 1, cpu, program );
    }

    ++agent %= NUM_AGENTS;
  }

  // prevent work from being optimized away
  for (const auto& cpu : collection) assert( cpu.GetNumCores() );

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

    uitsl::report_confidence<20>( res );

  }

};

Setup<1> s1;
Setup<32> s32;
Setup<1024> s1024;
Setup<32768> s32768;

// Run the benchmark
BENCHMARK_MAIN();
