#pragma once
#ifndef SGPL_DEBUG_SGPL_ALWAYS_ERROR_HPP_INCLUDE
#define SGPL_DEBUG_SGPL_ALWAYS_ERROR_HPP_INCLUDE

#include "sgpl_always_assert.hpp"

#define sgpl_always_error(...) sgpl_always_assert(0&&"unreachable", __VA_ARGS__)

#endif // #ifndef SGPL_DEBUG_SGPL_ALWAYS_ERROR_HPP_INCLUDE
