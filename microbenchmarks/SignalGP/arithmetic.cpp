#include <benchmark/benchmark.h>

#include "SignalGP/source/hardware/SignalGP/EventLibrary.h"
#include "SignalGP/source/hardware/SignalGP/SignalGPBase.h"
#include "SignalGP/source/hardware/SignalGP/impls/SignalGPToy.h"
#include "SignalGP/source/hardware/SignalGP/impls/SignalGPLinearProgram.h"
#include "SignalGP/source/hardware/SignalGP/impls/SignalGPLinearFunctionsProgram.h"
#include "SignalGP/source/hardware/SignalGP/utils/InstructionLibrary.h"
#include "SignalGP/source/hardware/SignalGP/utils/linear_program_instructions_impls.h"
#include "SignalGP/source/hardware/SignalGP/utils/linear_functions_program_instructions_impls.h"
#include "SignalGP/source/hardware/SignalGP/utils/MemoryModel.h"
#include "SignalGP/source/hardware/SignalGP/utils/LinearFunctionsProgram.h"
#include "SignalGP/source/random_utils.h"

template<typename HARDWARE_T, typename INSTRUCTION_T>
void Inst_Loop(HARDWARE_T & hw, const INSTRUCTION_T & inst) {
  auto & call_state = hw.GetCurThread().GetExecState().GetTopCallState();
  auto & mem_state = call_state.GetMemory();
  size_t cur_ip = call_state.GetIP();
  const size_t cur_mp = call_state.GetMP();
  emp_assert(cur_ip > 0);
  // CurIP is the next instruction (not the one currently executing)
  // Because IP gets incremented before execution, cur_ip should never be 0.
  const size_t bob = cur_ip - 1;
  const size_t eob = hw.FindEndOfBlock(cur_mp, cur_ip);
  const bool skip = false;
  if (skip) {
    // Skip to EOB
    call_state.SetIP(eob);
    // Advance past the block close if not at end of module.
    if (hw.IsValidProgramPosition(cur_mp, eob)) ++call_state.IP();
  } else {
    // Open flow
    emp_assert(cur_mp < hw.GetProgram().GetSize());
    hw.GetFlowHandler().OpenFlow(
      hw,
      {
        sgp::lsgp_utils::FlowType::WHILE_LOOP,
        cur_mp,
        cur_ip,
        bob,
        eob
      },
      hw.GetCurThread().GetExecState()
    );
  }
}


static void Vanilla_Arithmetic(benchmark::State& state) {

  using mem_model_t = sgp::SimpleMemoryModel;
  using signalgp_t = sgp::LinearFunctionsProgramSignalGP<
    mem_model_t,
    emp::BitSet<32>,
    int,
    emp::MatchBin<
      size_t,
      emp::HammingMetric<32>,
      emp::RankedSelector<std::ratio<16+8, 16>>,
      emp::AdditiveCountdownRegulator<>
    >,
    sgp::DefaultCustomComponent
  >;

  using inst_lib_t = typename signalgp_t::inst_lib_t;
  using inst_t = typename signalgp_t::inst_t;
  using inst_prop_t = typename signalgp_t::InstProperty;

  using event_lib_t = typename signalgp_t::event_lib_t;
  using program_t = typename signalgp_t::program_t;
  using tag_t = typename signalgp_t::tag_t;

  using mem_buffer_t = typename mem_model_t::mem_buffer_t;

  inst_lib_t inst_lib;
  event_lib_t event_lib;

  inst_lib.AddInst("Add", sgp::inst_impl::Inst_Add<signalgp_t, inst_t>, "");
  inst_lib.AddInst("Sub", sgp::inst_impl::Inst_Sub<signalgp_t, inst_t>, "");
  inst_lib.AddInst("Mult", sgp::inst_impl::Inst_Mult<signalgp_t, inst_t>, "");
  inst_lib.AddInst("Div", sgp::inst_impl::Inst_Div<signalgp_t, inst_t>, "");

  emp::Random rand;
  signalgp_t hardware(rand, inst_lib, event_lib);
  hardware.SetActiveThreadLimit(16);
  auto program {
    sgp::GenRandLinearFunctionsProgram<signalgp_t, 32>(
      rand,
      inst_lib,
      {1, 1}, // num functions
      1, // num func tags
      {100, 100}, // num instructions
      1, // num inst tags
      3, // num inst args
      {0, 5}
    )
  };

  inst_lib.AddInst(
    "Loop",
    Inst_Loop<signalgp_t, inst_t>,
    "",
    {inst_prop_t::BLOCK_DEF}
  );
  inst_lib.AddInst(
    "Close",
    sgp::inst_impl::Inst_Close<signalgp_t, inst_t>,
    "",
    {inst_prop_t::BLOCK_CLOSE}
  );

  program[0][0].SetID( inst_lib.GetID("Loop") );
  program[0][99].SetID( inst_lib.GetID("Close") );

  // Load program on hardware.
  hardware.SetProgram(program);

  // Spawn a thread to run the program.
  hardware.SpawnThreadWithID(0);

  assert( hardware.GetActiveThreadIDs().size() == 1 );

  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    for (size_t i{}; i < 16; ++i) hardware.SingleProcess();
  }

  assert( hardware.GetActiveThreadIDs().size() == 1 );


}

// Register the function as a benchmark
BENCHMARK(Vanilla_Arithmetic);
// Run the benchmark
BENCHMARK_MAIN();
