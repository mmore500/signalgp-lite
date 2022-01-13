#pragma once
#ifndef SGPL_UTILITY_RANDOM_SIGN_HPP_INCLUDE
#define SGPL_UTILITY_RANDOM_SIGN_HPP_INCLUDE

#include "ThreadLocalRandom.hpp"

namespace sgpl {

int random_sign(const double p_positive=0.5){
  return sgpl::tlrand.Get().P(p_positive) ? 1 : -1;
}

} // namespace sgpl

#endif // #ifndef SGPL_UTILITY_RANDOM_SIGN_HPP_INCLUDE
