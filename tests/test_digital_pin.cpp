#include <iostream>
#include <odroid/gpio.hpp>

auto main() -> int
{
   if (!gpio::is_ready()) {
      return 1;
   }

   namespace digital = gpio::digital;
   auto& digital_pin = gpio::get<digital::DigitalPin>(10, digital::Mode::OUTPUT);
   digital_pin.write(digital::IO::LOW);

   std::cout << "mode: " << static_cast<int>(digital_pin.mode()) << std::endl;
   std::cout << "pin_number: " << static_cast<int>(digital_pin.pin_number()) << std::endl;
   return 0;
}