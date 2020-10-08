#pragma once

#include <tuple>

#include "../hardware/Core.hpp"
#include "../program/Program.hpp"
#include "../program/Instruction.hpp"

namespace sgpl {

// tried a dispatch table, seemed to do about the same or worse
// https://eli.thegreenplace.net/2012/07/12/computed-goto-for-efficient-dispatch-tables
template<typename Spec>
inline void advance_core(
  sgpl::Core<Spec>& state,
  const sgpl::Program<Spec>& program,
  typename Spec::peripheral_t& peripheral
) {

  using library_t = typename Spec::library_t;

  const auto& instruction = program[ state.GetProgramCounter() ];

  emp_assert( instruction.op_code < library_t::GetSize() );

  switch( instruction.op_code ) {
    case 0:
      if constexpr (0 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<0>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 1:
      if constexpr (1 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<1>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 2:
      if constexpr (2 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<2>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 3:
      if constexpr (3 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<3>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 4:
      if constexpr (4 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<4>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 5:
      if constexpr (5 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<5>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 6:
      if constexpr (6 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<6>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 7:
      if constexpr (7 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<7>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 8:
      if constexpr (8 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<8>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 9:
      if constexpr (9 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<9>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 10:
      if constexpr (10 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<10>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 11:
      if constexpr (11 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<11>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 12:
      if constexpr (12 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<12>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 13:
      if constexpr (13 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<13>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 14:
      if constexpr (14 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<14>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 15:
      if constexpr (15 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<15>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 16:
      if constexpr (16 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<16>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 17:
      if constexpr (17 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<17>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 18:
      if constexpr (18 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<18>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 19:
      if constexpr (19 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<19>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 20:
      if constexpr (20 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<20>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 21:
      if constexpr (21 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<21>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 22:
      if constexpr (22 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<22>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 23:
      if constexpr (23 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<23>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
    case 24:
      if constexpr (24 < library_t::GetSize()) {
        using Functor = typename library_t::template Operation<24>;
        Functor::template run<Spec>(state, instruction, program, peripheral);
      }
    break;
  }

  state.AdvanceProgramCounter( program.size() );

};

template<typename Spec>

inline void execute_core(
  sgpl::Core<Spec>& state,
  const sgpl::Program<Spec>& program,
  typename Spec::peripheral_t& peripheral
) {

  for (size_t i{}; i < 16 && state.HasTerminated() == false; ++i) {
    advance_core<Spec>(state, program, peripheral);
  }

};

} // namespace sgpl
