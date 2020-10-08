#pragma once

#include <tuple>

#include "../hardware/Core.hpp"
#include "../program/Program.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

// tried a dispatch table, seemed to do about the same or worse
// https://eli.thegreenplace.net/2012/07/12/computed-goto-for-efficient-dispatch-tables
template<typename Library>
inline void advance_core(
  sgpl::Core<Library>& state, const sgpl::Program<Library>& program
) {

  const auto& instruction = program[ state.GetProgramCounter() ];

  emp_assert( instruction.op_code < Library::GetSize() );

  switch( instruction.op_code ) {
    case 0:
      if constexpr (0 < Library::GetSize()) {
        using Functor = typename Library::template Operation<0>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 1:
      if constexpr (1 < Library::GetSize()) {
        using Functor = typename Library::template Operation<1>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 2:
      if constexpr (2 < Library::GetSize()) {
        using Functor = typename Library::template Operation<2>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 3:
      if constexpr (3 < Library::GetSize()) {
        using Functor = typename Library::template Operation<3>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 4:
      if constexpr (4 < Library::GetSize()) {
        using Functor = typename Library::template Operation<4>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 5:
      if constexpr (5 < Library::GetSize()) {
        using Functor = typename Library::template Operation<5>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 6:
      if constexpr (6 < Library::GetSize()) {
        using Functor = typename Library::template Operation<6>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 7:
      if constexpr (7 < Library::GetSize()) {
        using Functor = typename Library::template Operation<7>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 8:
      if constexpr (8 < Library::GetSize()) {
        using Functor = typename Library::template Operation<8>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 9:
      if constexpr (9 < Library::GetSize()) {
        using Functor = typename Library::template Operation<9>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 10:
      if constexpr (10 < Library::GetSize()) {
        using Functor = typename Library::template Operation<10>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 11:
      if constexpr (11 < Library::GetSize()) {
        using Functor = typename Library::template Operation<11>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 12:
      if constexpr (12 < Library::GetSize()) {
        using Functor = typename Library::template Operation<12>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 13:
      if constexpr (13 < Library::GetSize()) {
        using Functor = typename Library::template Operation<13>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 14:
      if constexpr (14 < Library::GetSize()) {
        using Functor = typename Library::template Operation<14>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 15:
      if constexpr (15 < Library::GetSize()) {
        using Functor = typename Library::template Operation<15>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 16:
      if constexpr (16 < Library::GetSize()) {
        using Functor = typename Library::template Operation<16>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 17:
      if constexpr (17 < Library::GetSize()) {
        using Functor = typename Library::template Operation<17>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 18:
      if constexpr (18 < Library::GetSize()) {
        using Functor = typename Library::template Operation<18>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 19:
      if constexpr (19 < Library::GetSize()) {
        using Functor = typename Library::template Operation<19>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 20:
      if constexpr (20 < Library::GetSize()) {
        using Functor = typename Library::template Operation<20>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 21:
      if constexpr (21 < Library::GetSize()) {
        using Functor = typename Library::template Operation<21>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 22:
      if constexpr (22 < Library::GetSize()) {
        using Functor = typename Library::template Operation<22>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 23:
      if constexpr (23 < Library::GetSize()) {
        using Functor = typename Library::template Operation<23>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
    case 24:
      if constexpr (24 < Library::GetSize()) {
        using Functor = typename Library::template Operation<24>;
        Functor::template run<Library>( state, instruction, program );
      }
    break;
  }

  state.AdvanceProgramCounter( program.size() );

};

template<typename Library>
inline void execute_core(
  sgpl::Core<Library>& state, const sgpl::Program<Library>& program
) {

  for (size_t i{}; i < 16 && state.HasTerminated() == false; ++i) {
    advance_core<Library>(state, program);
  }

};

} // namespace sgpl
