#pragma once

#include "conduit/include/uitsl/debug/benchmark_utils.hpp"

#include "_SignalGP.hpp"

template<size_t NUM_AGENTS>
struct BenchHolder {

  std::function<program_t()> make_program;
  inst_lib_t& inst_lib_;
  event_lib_t& event_lib_;

  void Run(benchmark::State& state) {

    emp::Random rand{ 1 };
    emp::vector<signalgp_t> collection;
    collection.reserve( NUM_AGENTS );

    for (size_t i = 0; i < NUM_AGENTS; ++i) {
      collection.emplace_back(rand, inst_lib_, event_lib_);
      collection.back().SetActiveThreadLimit(16);
      collection.back().SetProgram(make_program());
      collection.back().SpawnThreadWithID(0);
      assert( collection.back().GetActiveThreadIDs().size() == 1 );
    }

    size_t agent{};

    emp::vector< emp::BitSet<64> > tags;
    tags.reserve( 20 );
    std::generate_n(
      std::back_inserter(tags),
      20,
      [&]{ return emp::BitSet<64>(rand); }
    );
    size_t tag{};

    // Perform setup here
    for (auto _ : state) {
      // prevent loop from getting optimized out under
      // control conditions and when n = 1
      int do_not_optimize{};
      uitsl::do_not_optimize(do_not_optimize);

      auto& cpu = collection[agent];
#ifndef STRIP_BENCHMARK_LOOP
      // This code gets timed
      if constexpr ( fill_cores ) {
      while ( cpu.GetUnusedThreadIDs().size() ) {
        cpu.SpawnThreadWithTag( tags[tag] );
        ++tag %= tags.size();
      }
      cpu.SingleProcess();
      } else {
        for (size_t i{}; i < 16; ++i) cpu.SingleProcess();
      }
#endif // #ifndef STRIP_BENCHMARK_LOOP
        ++agent %= NUM_AGENTS;
    }

    for (auto& hardware : collection) {
      assert( hardware.GetActiveThreadIDs().size() == 1 );
    }

    uitsl::do_not_optimize(agent);

    state.counters["num agents"] = NUM_AGENTS;

  }

};
