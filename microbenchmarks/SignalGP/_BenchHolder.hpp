#pragma once

#include "_SignalGP.hpp"

template<size_t NUM_AGENTS>
struct BenchHolder {

  program_t& program;
  inst_lib_t& inst_lib;
  event_lib_t& event_lib;


  void Run(benchmark::State& state) {

    emp::Random rand;
    emp::vector<signalgp_t> collection;

    for (size_t i = 0; i < NUM_AGENTS; ++i) {
      collection.emplace_back(rand, inst_lib, event_lib);
      collection.back().SetActiveThreadLimit(16);
      collection.back().SetProgram(program);
      collection.back().SpawnThreadWithID(0);
      assert( collection.back().GetActiveThreadIDs().size() == 1 );
    }

    size_t agent{};

    // Perform setup here
    for (auto _ : state) {
      // This code gets timed
      for (size_t i{}; i < 16; ++i) collection[agent].SingleProcess();

      ++agent %= NUM_AGENTS;

    }

    for (auto& hardware : collection) {
      assert( hardware.GetActiveThreadIDs().size() == 1 );
    }

  }

};
