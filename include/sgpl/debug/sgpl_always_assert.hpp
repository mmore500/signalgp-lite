#pragma once
#ifndef SGPL_DEBUG_SGPL_ALWAYS_ASSERT_HPP_INCLUDE
#define SGPL_DEBUG_SGPL_ALWAYS_ASSERT_HPP_INCLUDE

#include <cstdlib>
#include <iostream>

#include "../../../third-party/conduit/include/uitsl/meta/fwd_or_cast.hpp"
#include "../../../third-party/conduit/include/uitsl/meta/is_streamable.hpp"
#include "../../../third-party/conduit/include/uitsl/utility/SetSeparator.hpp"

#include "SGPL_STRINGIFY.hpp"

#ifndef SGPL_UITSL_NAMESPACE
#define SGPL_UITSL_NAMESPACE() uitsl
#endif // #ifndef SGPL_UITSL_NAMESPACE

// adapted from https://stackoverflow.com/a/53986818
// pass optional second argument as myvar << "mystring" << etc.
#define sgpl_always_assert(expr, ...)                                         \
do {                                                                          \
  if(!(expr)) {                                                               \
    namespace uitsl_ns = SGPL_UITSL_NAMESPACE();                              \
    std::cout << '\n';                                                        \
    std::cout << '\n';                                                        \
    std::cout << "ASSERTION FAILED: ";                                        \
    std::cout << '\n';                                                        \
    std::cout << SGPL_STRINGIFY(expr) << " was ";                             \
    std::cout << uitsl_ns::fwd_or_cast<uitsl_ns::is_streamable, bool>(expr);  \
    std::cout << '\n';                                                        \
    std::cout << '\n';                                                        \
    std::cout << "FILE: " << __FILE__ << '\n';                                \
    std::cout << "FUNCTION: " << __PRETTY_FUNCTION__ << '\n';                 \
    std::cout << "LINE: " << __LINE__ << '\n';                                \
    std::cout << '\n';                                                        \
    std::cout << "MESSAGE:\n";                                                \
    std::cout << SGPL_STRINGIFY(__VA_ARGS__) << '\n';                         \
    std::cout << uitsl_ns::SetSeparator(" << ") << __VA_ARGS__;\
    std::cout << '\n';                                                        \
    std::abort();                                                             \
  }                                                                           \
} while(0)

// no clang support for __VA_OPT__ yet
// std::cout << uitsl_ns::SetSeparator(" << ") __VA_OPT__(<<) __VA_ARGS__;\


#endif // #ifndef SGPL_DEBUG_SGPL_ALWAYS_ASSERT_HPP_INCLUDE
