#include <iostream>
#include <odroid/gpio.hpp>

constexpr uint16_t PIN_NUMBER = 23; // physical pin 33 on droid n2
namespace pwm = gpio::pwm;
auto main() -> int
{
   if (!gpio::setup()) {
      return 1;
   }

   auto& pwm_pin = gpio::get<pwm::PWMPin>(PIN_NUMBER, pwm::Mode::OUTPUT);
   // set clock or range here optionally
   // pwm::clock(128) in hz
   // pwm::range(500) some range here
   pwm_pin.duty_cycle(50); // Some duty cycle [0, 100]

   return 0;
}
