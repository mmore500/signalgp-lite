#pragma once
#ifndef SGPL_PROGRAM_PROGRAM_HPP_INCLUDE
#define SGPL_PROGRAM_PROGRAM_HPP_INCLUDE

#include <algorithm>
#include <cstddef>

#include "../../../third-party/cereal/include/cereal/types/vector.hpp"
#include "../../../third-party/Empirical/source/base/vector.h"
#include "../../../third-party/Empirical/source/polyfill/span.h"
#include "../../../third-party/Empirical/source/tools/hash_utils.h"
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

  /// Default constructor.
  Program() = default;

  Program( const size_t n ) : parent_t( n ) {
    sgpl::ThreadLocalRandom::Get().RandFill(
      reinterpret_cast<unsigned char*>( this->data() ),
      size_bytes()
    );
    Rectify();
  }

  /// Copy constructor.
  Program( const Program& other ) : parent_t(other) {}

  /// Move constructor.
  Program( Program&& other ) : parent_t( std::move(other) ) {}

  /// Raw copy constructor.
  Program( const parent_t& other ) : parent_t(other) {}

  /// Raw move constructor.
  Program( parent_t&& other ) : parent_t( std::move(other) ) {}

  /// Copy assignment operator.
  Program& operator=(const Program& other) {
    parent_t::operator=(other);
    return *this;
  }

  /// Move assignment operator.
  Program& operator=(Program&& other) {
    parent_t::operator=( std::move(other) );
    return *this;
 }

  /// Raw move assignment operator.
  Program& operator=(parent_t&& other) {
    parent_t::operator=( std::move(other) );
    return *this;
 }

  size_t ApplyPointMutations(
    const float p_byte_scramble, const rectifier_t& rectifier=rectifier_t{}
  ) {

    // ideally, we would draw from the binomial distn,
    // but that's expensive with varying n...
    // so approximate with the poisson distribution instead
    // they're similar-ish, e.g., https://www.researchgate.net/figure/Poisson-versus-binomial-distribution-from-number-of-heads-in-a-coin-toss-The-Poisson_fig3_255717571
    // (they become more similar for large n)
    const size_t n_muts = sgpl::ThreadLocalRandom::Get().GetRandPoisson(
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

  void RotateGlobalAnchorToFront() {

    const auto first_anchor = std::find_if(
      this->begin(),
      this->end(),
      []( const auto& instruction ) {
        return library_t::IsAnchorGlobalOpCode( instruction.op_code );
      }
    );

    if ( first_anchor != this->end() ) std::rotate(
      this->begin(),
      first_anchor,
      this->end()
    );

  }

};

} // namespace sgpl

namespace std {

template <typename Spec>
struct hash<sgpl::Program<Spec>> {

  size_t operator()( const sgpl::Program<Spec>& program ) const {
    return emp::murmur_hash( std::span<const std::byte>(
      reinterpret_cast<const std::byte*>( program.data() ),
      program.size() * sizeof( program.front() )
    ) );
  }

};

} // namespace std


#endif // #ifndef SGPL_PROGRAM_PROGRAM_HPP_INCLUDE
