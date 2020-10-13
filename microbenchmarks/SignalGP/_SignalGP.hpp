#pragma once

#include "SignalGP/source/hardware/SignalGP/EventLibrary.h"
#include "SignalGP/source/hardware/SignalGP/impls/SignalGPLinearFunctionsProgram.h"
#include "SignalGP/source/hardware/SignalGP/impls/SignalGPLinearProgram.h"
#include "SignalGP/source/hardware/SignalGP/impls/SignalGPToy.h"
#include "SignalGP/source/hardware/SignalGP/SignalGPBase.h"
#include "SignalGP/source/hardware/SignalGP/utils/InstructionLibrary.h"
#include "SignalGP/source/hardware/SignalGP/utils/LinearFunctionsProgram.h"
#include "SignalGP/source/hardware/SignalGP/utils/linear_functions_program_instructions_impls.h"
#include "SignalGP/source/hardware/SignalGP/utils/linear_program_instructions_impls.h"
#include "SignalGP/source/hardware/SignalGP/utils/MemoryModel.h"
#include "SignalGP/source/random_utils.h"

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
