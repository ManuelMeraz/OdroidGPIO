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

   std::cout << "mode: " << static_cast<uint16_t>(digital_pin.mode()) << std::endl;
   std::cout << "pin_number: " << digital_pin.pin_number() << std::endl;

   digital_pin.mode(digital::Mode::INPUT);

   auto& second_pin_instance = gpio::get<digital::DigitalPin>(10);
   std::cout << "second instance mode: " << static_cast<uint16_t>(second_pin_instance.mode())
             << std::endl;

   std::cout << "first instance mode should be 0 -> " << static_cast<uint16_t>(digital_pin.mode())
             << std::endl;

   namespace pwm = gpio::pwm;
   try {
      gpio::get<pwm::PWMPin>(10, pwm::Mode::OUTPUT);
      std::cerr << "Failed to catch incorrect pin type." << std::endl;
      return 1;
   } catch (const std::invalid_argument& e) {
      std::cout << "Caught incorrect pin type. Passed." << std::endl;
   }

   return 0;
}