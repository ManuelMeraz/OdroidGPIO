#ifndef ODROIDGPIO_DIGITAL_HPP
#define ODROIDGPIO_DIGITAL_HPP

#include <cstdint>
#include <memory>

namespace gpio::digital {
enum class Mode : uint16_t { INPUT = 0, OUTPUT = 1, OFF = 0 };
enum class Write : uint16_t { LOW = 0, HIGH = 1 };
} // namespace gpio::digital

#endif // ODROIDGPIO_DIGITAL_HPP
