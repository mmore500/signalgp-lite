#pragma once

#include <tuple>

#include "../hardware/Core.hpp"
#include "../program/Program.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

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
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 1:
      if constexpr (1 < Library::GetSize()) {
        using Functor = typename Library::template Operation<1>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 2:
      if constexpr (2 < Library::GetSize()) {
        using Functor = typename Library::template Operation<2>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 3:
      if constexpr (3 < Library::GetSize()) {
        using Functor = typename Library::template Operation<3>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 4:
      if constexpr (4 < Library::GetSize()) {
        using Functor = typename Library::template Operation<4>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 5:
      if constexpr (5 < Library::GetSize()) {
        using Functor = typename Library::template Operation<5>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 6:
      if constexpr (6 < Library::GetSize()) {
        using Functor = typename Library::template Operation<6>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 7:
      if constexpr (7 < Library::GetSize()) {
        using Functor = typename Library::template Operation<7>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 8:
      if constexpr (8 < Library::GetSize()) {
        using Functor = typename Library::template Operation<8>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 9:
      if constexpr (9 < Library::GetSize()) {
        using Functor = typename Library::template Operation<9>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 10:
      if constexpr (10 < Library::GetSize()) {
        using Functor = typename Library::template Operation<10>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 11:
      if constexpr (11 < Library::GetSize()) {
        using Functor = typename Library::template Operation<11>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 12:
      if constexpr (12 < Library::GetSize()) {
        using Functor = typename Library::template Operation<12>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 13:
      if constexpr (13 < Library::GetSize()) {
        using Functor = typename Library::template Operation<13>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 14:
      if constexpr (14 < Library::GetSize()) {
        using Functor = typename Library::template Operation<14>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 15:
      if constexpr (15 < Library::GetSize()) {
        using Functor = typename Library::template Operation<15>;
        Functor::template run<Library>( state, instruction );
      }
    break;
    case 16:
      if constexpr (16 < Library::GetSize()) {
        using Functor = typename Library::template Operation<16>;
        Functor::template run<Library>( state, instruction );
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
