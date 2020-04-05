#include <iostream>
#include <odroid/gpio.hpp>

auto main() -> int
{
   if (!gpio::is_ready()) {
      return 1;
   }

   namespace digital = gpio::digital;
   auto& digital_pin = gpio::get<digital::DigitalPin>(10, digital::Mode::OUTPUT);
   digital_pin.write(digital::Write::LOW);

   std::cout << "pin_number: " << digital_pin.pin_number() << std::endl;
   return 0;
}