#pragma once
#ifndef SGPL_DEBUG_SGPL_ASSERT_HPP_INCLUDE
#define SGPL_DEBUG_SGPL_ASSERT_HPP_INCLUDE

#include "sgpl_always_assert.hpp"

#ifndef NDEBUG
#define sgpl_assert(expr, ...) sgpl_always_assert(expr, __VA_ARGS__)
#else
#define sgpl_assert(expr, ...)
#endif // #ifndef NDEBUG

#endif // #ifndef SGPL_DEBUG_SGPL_ASSERT_HPP_INCLUDE
