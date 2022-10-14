#pragma once
#ifndef SGPL_PROGRAM_LOAD_PROGRAM_HPP_INCLUDE
#define SGPL_PROGRAM_LOAD_PROGRAM_HPP_INCLUDE

#include <fstream>
#include <string>

#include "../../../third-party/cereal/include/cereal/archives/binary.hpp"
#include "../../../third-party/cereal/include/cereal/archives/json.hpp"
#include "../../../third-party/cereal/include/cereal/cereal.hpp"
#include "../../../third-party/conduit/include/uitsl/polyfill/filesystem.hpp"

#include "../debug/sgpl_error.hpp"

#include "Program.hpp"

namespace sgpl {

template <typename Spec>
sgpl::Program<Spec> load_program(const std::filesystem::path& path) {
  sgpl::Program<Spec> program;

  std::ifstream is(path);

  if (path.extension() == ".json") {
    cereal::JSONInputArchive archive( is );
  } else if (path.extension() == ".bin") {
    cereal::BinaryInputArchive archive( is );
  } else {
    sgpl_error("Unknown extension." << path << path.extension());
  }

  archive( program );

  return program;
}

} // namespace sgpl

#endif // #ifndef SGPL_PROGRAM_LOAD_PROGRAM_HPP_INCLUDE
