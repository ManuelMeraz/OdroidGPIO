#include <iostream>
#include <odroid/gpio.hpp>

auto main() -> int
{
   if (!gpio::is_ready()) {
      return 1;
   }

   namespace pwm = gpio::pwm;
   auto& pwm_pin = gpio::get<pwm::PWMPin>(37, pwm::Mode::OUTPUT);

   std::cout << "mode: " << static_cast<int>(pwm_pin.mode()) << std::endl;
   std::cout << "pin_number: " << static_cast<int>(pwm_pin.pin_number()) << std::endl;
   return 0;
}
