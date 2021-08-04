#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/operations/binary/Add.hpp"

#include "_BenchSpec.hpp"
#include "benchmark.hpp"

TEST_CASE("Test Add") {

  // TODO flesh out stub test
  sgpl::Add{};

}

TEST_CASE("Benchmark Add", "[benchmark]") {
  Setup<1> s1;
  Setup<32> s32;
  Setup<1024> s1024;
  Setup<32768> s32768;

  // Run the benchmark
  BENCHMARK_MAIN();
}
