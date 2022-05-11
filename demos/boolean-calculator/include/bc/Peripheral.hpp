#pragma once

namespace bc {

struct Peripheral {

  uint32_t output{};
  uint32_t input{};
  emp::array<float, 8> global_registers{};

};

} // namespace bc
