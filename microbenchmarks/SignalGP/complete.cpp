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

#include "sgpl/utility/ThreadLocalRandom.hpp"

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


static void Vanilla_Complete(benchmark::State& state) {

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

  inst_lib.AddInst("Fork", sgp::inst_impl::Inst_Fork<signalgp_t, inst_t>, "");
  inst_lib.AddInst("Nop", sgp::inst_impl::Inst_Nop<signalgp_t, inst_t>, "");
  inst_lib.AddInst(
    "Terminate", sgp::inst_impl::Inst_Terminate<signalgp_t, inst_t>, ""
  );
  inst_lib.AddInst("Add", sgp::inst_impl::Inst_Add<signalgp_t, inst_t>, "");
  inst_lib.AddInst("Div", sgp::inst_impl::Inst_Div<signalgp_t, inst_t>, "");
  inst_lib.AddInst("Mod", sgp::inst_impl::Inst_Mod<signalgp_t, inst_t>, "");
  inst_lib.AddInst(
    "Mult", sgp::inst_impl::Inst_Mult<signalgp_t, inst_t>, ""
  );
  inst_lib.AddInst(
    "Sub", sgp::inst_impl::Inst_Sub<signalgp_t, inst_t>, ""
  );
  inst_lib.AddInst("TestEqu", sgp::inst_impl::Inst_TestEqu<signalgp_t, inst_t>, "");
  inst_lib.AddInst(
    "TestLess", sgp::inst_impl::Inst_TestLess<signalgp_t, inst_t>, ""
  );
  inst_lib.AddInst(
    "TestNEqu", sgp::inst_impl::Inst_TestNEqu<signalgp_t, inst_t>, ""
  );
  inst_lib.AddInst("Call", sgp::inst_impl::Inst_Fork<signalgp_t, inst_t>, "");
  inst_lib.AddInst(
    "Routine", sgp::inst_impl::Inst_Fork<signalgp_t, inst_t>, ""
  );

  inst_lib.AddInst(
    "If",
    sgp::inst_impl::Inst_Div<signalgp_t, inst_t>,
    "",
    {inst_prop_t::BLOCK_DEF}
  );
  inst_lib.AddInst(
    "While",
    sgp::inst_impl::Inst_Div<signalgp_t, inst_t>,
    "",
    {inst_prop_t::BLOCK_DEF}
  );
  inst_lib.AddInst(
    "Countdown",
    sgp::inst_impl::Inst_Div<signalgp_t, inst_t>,
    "",
    {inst_prop_t::BLOCK_DEF}
  );
  inst_lib.AddInst(
    "Close",
    sgp::inst_impl::Inst_Close<signalgp_t, inst_t>,
    "",
    {inst_prop_t::BLOCK_CLOSE}
  );

  inst_lib.AddInst(
    "AdjRegulator", sgp::inst_impl::Inst_AdjRegulator<signalgp_t, inst_t>, ""
  );
  inst_lib.AddInst(
    "SenseRegulator", sgp::inst_impl::Inst_SenseRegulator<signalgp_t, inst_t>, ""
  );
  inst_lib.AddInst(
    "SetRegulator", sgp::inst_impl::Inst_SetRegulator<signalgp_t, inst_t>, ""
  );
  inst_lib.AddInst("Call", sgp::inst_impl::Inst_Call<signalgp_t, inst_t>, "");
  inst_lib.AddInst("Dec", sgp::inst_impl::Inst_Dec<signalgp_t, inst_t>, "");
  inst_lib.AddInst(
    "Generate",
    [](signalgp_t& hw, const inst_t& inst) {
      auto & call_state = hw.GetCurThread().GetExecState().GetTopCallState();
      // Increment value in local memory @ [ARG0]
      call_state.GetMemory().AccessWorking(inst.GetArg(0))
        = sgpl::ThreadLocalRandom::Get().GetDouble();
    },
    ""
  );
  inst_lib.AddInst("Inc", sgp::inst_impl::Inst_Inc<signalgp_t, inst_t>, "");
  inst_lib.AddInst(
    "Negate",
    [](signalgp_t& hw, const inst_t& inst) {
      auto & call_state = hw.GetCurThread().GetExecState().GetTopCallState();
      // Increment value in local memory @ [ARG0]
      call_state.GetMemory().AccessWorking(inst.GetArg(0)) *= -1;
    },
    ""
  );
  inst_lib.AddInst("Not", sgp::inst_impl::Inst_Not<signalgp_t, inst_t>, "");
  inst_lib.AddInst(
    "Terminal", sgp::inst_impl::Inst_Terminal<signalgp_t, inst_t>, ""
  );

  emp::Random rand;
  signalgp_t hardware(rand, inst_lib, event_lib);
  hardware.SetActiveThreadLimit(16);
  auto program {
    sgp::GenRandLinearFunctionsProgram<signalgp_t, 32>(
      rand,
      inst_lib,
      {5, 5}, // num functions
      1, // num func tags
      {20, 20}, // num instructions
      1, // num inst tags
      3, // num inst args
      {0, 5}
    )
  };

  // Load program on hardware.
  hardware.SetProgram(program);

  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    while ( hardware.GetNumUnusedThreads() ) {
      hardware.SpawnThreadWithTag( emp::BitSet<32>(rand) );
    }

    hardware.SingleProcess();
  }

  assert( hardware.GetActiveThreadIDs().size() );


}

// Register the function as a benchmark
BENCHMARK(Vanilla_Complete);
// Run the benchmark
BENCHMARK_MAIN();
