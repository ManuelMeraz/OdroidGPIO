#include "detail/digital/digital.hpp"

#include <wiringPi.h>

void gpio::digital::write(uint16_t pin_number, IO mode)
{
   digitalWrite(pin_number, static_cast<int>(mode));
}

gpio::digital::IO gpio::digital::read(uint16_t pin_number)
{
   return static_cast<IO>(digitalRead(static_cast<int>(pin_number)));
}
