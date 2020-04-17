#include "detail/pwm/pwm.hpp"

#include <odroid/pwm/pwm.hpp>
#include <wiringPi.h>

void gpio::pwm::duty_cycle(uint16_t pin_number, uint16_t duty_cycle)
{
   pwmWrite(pin_number, duty_cycle);
}

[[maybe_unused]] void gpio::pwm::clock(uint16_t hz)
{
   pwmSetClock(hz);
}

[[maybe_unused]] void gpio::pwm::range(uint16_t range)
{
   pwmSetRange(range);
}
