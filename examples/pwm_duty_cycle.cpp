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

   constexpr uint8_t DUTY_CYCLE_PERCENT = 50;
   pwm_pin.duty_cycle(DUTY_CYCLE_PERCENT);

   return 0;
}
