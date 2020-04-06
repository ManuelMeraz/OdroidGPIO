#include <iostream>
#include <odroid/gpio.hpp>

constexpr uint8_t PIN{0};
constexpr size_t NUM_LOOPS{1000};

using namespace std::chrono_literals;
namespace digital = gpio::digital;

auto main() -> int
{
   if (!gpio::setup()) {
      return 1;
   }

   auto& pin = gpio::get<digital::DigitalPin>(PIN, digital::Mode::OUTPUT);

   for (size_t count = 0; count < NUM_LOOPS; ++count) {
      std::cout << "Turning LED on!" << std::endl;
      pin.write(digital::IO::HIGH);
      gpio::sleep(1s);

      std::cout << "Turning LED off..." << std::endl;
      pin.write(digital::IO::LOW);
      gpio::sleep(1s);
   }

   return 0;
}
