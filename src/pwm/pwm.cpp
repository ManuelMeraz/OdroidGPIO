#include "detail/pwm/pwm.hpp"

#include <odroid/pwm/pwm.hpp>
#include <wiringPi.h>

void gpio::pwm::duty_cycle(uint8_t pin_number, uint8_t duty_cycle)
{
   pwmWrite(pin_number, duty_cycle);
}

void gpio::pwm::clock(uint8_t hz)
{
   pwmSetClock(hz);
}
void gpio::pwm::range(uint16_t range)
{
   pwmSetRange(range);
}
