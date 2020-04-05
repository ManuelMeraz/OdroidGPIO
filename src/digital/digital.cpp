#include "detail/digital/digital.hpp"

#include <wiringPi.h>

void gpio::digital::write(uint16_t pin_number, Write mode)
{
   digitalWrite(pin_number, static_cast<int>(mode));
}
