#include "detail/gpio.hpp"

#include <odroid/gpio.hpp>
#include <wiringPi.h>

auto gpio::setup() -> bool
{
   return wiringPiSetup() != -1;
}

void gpio::pin_mode(uint16_t pin_number, uint16_t mode)
{
   pinMode(static_cast<int>(pin_number), static_cast<int>(mode));
}

void gpio::sleep(std::chrono::milliseconds duration)
{
   ::delay(static_cast<int>(duration.count()));
}
