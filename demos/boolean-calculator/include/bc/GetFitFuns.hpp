#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <tuple>

#include "Empirical/include/emp/base/vector.hpp"
#include "Empirical/include/emp/Evolve/World.hpp"

#include "Organism.hpp"
#include "TestCase.hpp"
#include "load_training_set.hpp"

namespace bc {

template <typename Spec>
auto GetFitFuns(bool verbose = false) {
  emp::vector< std::function<double(const bc::Organism<Spec>&)> > fit_funs;

  const emp::vector<bc::TestCase>& training_set = bc::load_training_set(); // load training set by ref

  // emp_assert(
  //     grouped_set.size() == magic_enum::enum_count<bc::PromptEnum>() - 1, // ignore NUM
  //     "Missing operations in test cases.");

  emp::vector<int> indices(training_set.size());
  std::iota(
    indices.begin(),
    indices.end(),
    0
  );

  emp::Shuffle(sgpl::tlrand.Get(), indices);

  // test first 25 cases
  for (size_t i{}; i < 25; i++) {
    const auto& case_ = training_set[ indices[i] ];

    fit_funs.push_back(
      [&case_, verbose](const bc::Organism<Spec>& org) -> double {
        return org.Evaluate(case_, verbose);
      }
    );
  }

  return fit_funs;
}

}
