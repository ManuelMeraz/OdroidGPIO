#ifndef DETAIL_ODROIDGPIO_PWM_HPP
#define DETAIL_ODROIDGPIO_PWM_HPP

#include <cstdint>

namespace gpio::pwm {
void duty_cycle(uint8_t pin_number, uint8_t duty_cycle);
}

#endif // DETAIL_ODROIDGPIO_PWM_HPP
