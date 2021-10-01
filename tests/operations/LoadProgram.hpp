#include <fstream>
#include <string>

#include "cereal/include/cereal/archives/json.hpp"
#include "cereal/include/cereal/cereal.hpp"

#include "sgpl/program/Program.hpp"

namespace sgpl::test {

template <typename Spec>
sgpl::Program<Spec> LoadProgram(const std::string& name) {
  sgpl::Program<Spec> program;

  std::ifstream is("assets/" + name + ".json");

  cereal::JSONInputArchive archive( is );

  archive( program );

  return program;
}

};
