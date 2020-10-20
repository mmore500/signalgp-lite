#pragma once
#ifndef SGPL_PROGRAM_PROGRAM_HPP_INCLUDE
#define SGPL_PROGRAM_PROGRAM_HPP_INCLUDE

#include <algorithm>
#include <cstddef>

#include "../../../third-party/cereal/include/cereal/types/vector.hpp"
#include "../../../third-party/Empirical/source/base/vector.h"
#include "../../../third-party/Empirical/source/tools/Random.h"

#include "../algorithm/mutate_bytes.hpp"
#include "../utility/ThreadLocalRandom.hpp"

#include "Instruction.hpp"
#include "OpCodeRectifier.hpp"

namespace sgpl {

template<typename Spec>
class Program : public emp::vector<sgpl::Instruction<Spec>> {

  using parent_t = emp::vector<sgpl::Instruction<Spec>>;
  using library_t = typename Spec::library_t;
  using rectifier_t = sgpl::OpCodeRectifier<library_t>;

  size_t size_bytes() const {
    return this->size() * sizeof( typename parent_t::value_type );
  }

  void Rectify(const rectifier_t& rectifier=rectifier_t{}) {
    for (auto& inst : *this) inst.Rectify(rectifier);
  }

public:

  Program() = default;

  Program( const size_t n ) : parent_t( n ) {
    sgpl::ThreadLocalRandom::Get().RandFill(
      reinterpret_cast<unsigned char*>( this->data() ),
      size_bytes()
    );
    Rectify();
  }

  size_t Perturb(
    const float p_byte_scramble, const rectifier_t& rectifier=rectifier_t{}
  ) {

    // TODO optimize?
    const size_t n_muts = sgpl::ThreadLocalRandom::Get().GetRandBinomial(
      size_bytes(),
      p_byte_scramble
    );

    sgpl::mutate_bytes(
      std::span<std::byte>(
        reinterpret_cast<std::byte*>( this->data() ),
        size_bytes()
      ),
      n_muts
    );

    Rectify();

    return n_muts;

  }


};

} // namespace sgpl

#endif // #ifndef SGPL_PROGRAM_PROGRAM_HPP_INCLUDE
