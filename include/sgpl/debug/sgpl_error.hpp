#pragma once
#ifndef SGPL_DEBUG_SGPL_ERROR_HPP_INCLUDE
#define SGPL_DEBUG_SGPL_ERROR_HPP_INCLUDE

#include "sgpl_always_assert.hpp"

#ifndef NDEBUG
#define sgpl_error(...) sgpl_always_assert(0 && "unreachable", __VA_ARGS__)
#else
#define sgpl_error(...)
#endif // #ifndef NDEBUG

#endif // #ifndef SGPL_DEBUG_SGPL_ERROR_HPP_INCLUDE
