#ifndef ODROID_GPIO_PWM_HPP
#define ODROID_GPIO_PWM_HPP

#include <cstdint>

namespace gpio::pwm {
enum class Mode : int { OUTPUT = 4, SOFT_OUTPUT = 6, TONE_OUTPUTOFF = 8, OFF = 0 };

void clock(uint16_t hz);
void range(uint16_t range);
} // namespace gpio::pwm

#endif // ODROIDGPIO_PWM_HPP
