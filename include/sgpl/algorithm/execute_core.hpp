#pragma once

#include <tuple>

#include "../hardware/Core.hpp"
#include "../program/Program.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

template<typename Library>
inline void advance_core(sgpl::Core& state, const sgpl::Program& program) {

  const sgpl::Instruction& instruction = program[state.inst_counter];

  switch( instruction.op_code ) {
    case 0:
      if constexpr (0 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<0, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 1:
      if constexpr (1 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<1, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 2:
      if constexpr (2 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<2, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 3:
      if constexpr (3 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<3, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 4:
      if constexpr (4 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<4, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 5:
      if constexpr (5 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<5, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 6:
      if constexpr (6 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<6, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 7:
      if constexpr (7 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<7, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 8:
      if constexpr (8 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<8, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 9:
      if constexpr (9 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<9, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 10:
      if constexpr (10 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<10, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 11:
      if constexpr (11 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<11, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 12:
      if constexpr (12 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<12, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 13:
      if constexpr (13 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<13, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 14:
      if constexpr (14 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<14, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 15:
      if constexpr (15 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<15, Library>::type;
        Functor::run( state, instruction );
      }
    break;
    case 16:
      if constexpr (16 < std::tuple_size<Library>::value) {
        using Functor = typename std::tuple_element<16, Library>::type;
        Functor::run( state, instruction );
      }
    break;
  }

  ++state.inst_counter %= program.size();

};

template<typename Library>
inline void execute_core(Core& state, const Program& program) {

  for (size_t i{}; i < 16; ++i) advance_core<Library>(state, program);

};

} // namespace sgpl
