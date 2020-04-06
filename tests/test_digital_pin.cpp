#include <iostream>
#include <odroid/gpio.hpp>

auto main() -> int
{
   if (!gpio::setup()) {
      return 1;
   }

   namespace digital = gpio::digital;
   auto& digital_pin = gpio::get<digital::DigitalPin>(10, digital::Mode::OUTPUT);
   digital_pin.write(digital::IO::LOW);

   std::cout << "mode: " << static_cast<int>(digital_pin.mode()) << std::endl;
   std::cout << "pin_number: " << static_cast<int>(digital_pin.pin_number()) << std::endl;

   digital_pin.mode(digital::Mode::INPUT);

   auto& second_pin_instance = gpio::get<digital::DigitalPin>(10);
   std::cout << "second instance mode: " << static_cast<int>(second_pin_instance.mode())
             << std::endl;

   std::cout << "first instance mode should be 0 -> " << static_cast<int>(digital_pin.mode())
             << std::endl;
   return 0;
}