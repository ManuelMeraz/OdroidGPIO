#ifndef ODROID_GPIO_PWM_HPP
#define ODROID_GPIO_PWM_HPP

#include <cstdint>

namespace gpio::pwm {
enum class Mode : int { OUTPUT = 4, OFF = 0 };

[[maybe_unused]] void clock(uint16_t hz);
[[maybe_unused]] void range(uint16_t range);
} // namespace gpio::pwm

#endif // ODROIDGPIO_PWM_HPP
