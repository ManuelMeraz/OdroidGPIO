#include <iostream>
#include <odroid/gpio.hpp>

constexpr uint16_t PIN_NUMBER{0}; // physical pin 11 on odroid n2

using namespace std::chrono_literals;
namespace digital = gpio::digital;

auto main() -> int
{
   auto& pin = gpio::get<digital::DigitalPin>(PIN_NUMBER, digital::Mode::OUTPUT);

   while (true) {
      std::cout << "Turning LED on!" << std::endl;
      pin.write(digital::IO::HIGH);
      gpio::sleep(1s);

      std::cout << "Turning LED off..." << std::endl;
      pin.write(digital::IO::LOW);
      gpio::sleep(1s);
   }

   return 0;
}
