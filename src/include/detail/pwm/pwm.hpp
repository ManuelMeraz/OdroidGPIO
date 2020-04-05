#ifndef ODROIDGPIO_PWM_HPP
#define ODROIDGPIO_PWM_HPP

#include <cstdint>

namespace gpio::pwm {
void duty_cycle(uint8_t pin_number, uint8_t duty_cycle);
}

#endif // ODROIDGPIO_PWM_HPP
