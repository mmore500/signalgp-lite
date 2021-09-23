#pragma once

namespace bc {

struct Peripheral {

  uint32_t output{};
  emp::array<float, 8> global_registers{};

};

} // namespace bc
