#ifndef ODROID_GPIO_DIGITAL_HPP
#define ODROID_GPIO_DIGITAL_HPP

#include <cstdint>
#include <memory>

namespace gpio::digital {
enum class Mode : uint8_t { INPUT = 0, OUTPUT = 1, OFF = 0 };
enum class Write : uint8_t { LOW = 0, HIGH = 1 };
} // namespace gpio::digital

#endif // ODROID_GPIO_DIGITAL_HPP
