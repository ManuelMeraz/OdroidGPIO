#include <iostream>
#include <odroid/gpio.hpp>
#include <sstream>

// These pins actually aren't needed to do I2C communication, but for code safety
// It prevents these pins from being enabled by accident
constexpr uint8_t SDA_PIN{8}; // physical pin 3 on odroid n2
constexpr uint8_t SCL_PIN{9}; // physical pin 5 on odroid n2
constexpr uint32_t REGISTER_ADDRESS = 0xFFD1D000;

// SDA.2 and SCL.2
constexpr uint8_t DEVICE_NUMBER{2};
namespace I2C = gpio::I2C;

auto main() -> int
{
   if (!gpio::setup()) {
      return 1;
   }

   auto& I2C_device = I2C::I2CDevice::get(DEVICE_NUMBER, SDA_PIN, SCL_PIN);
   auto buffer = I2C_device.read<32>(0);

   while (true) {
      std::stringstream ss;
      for (uint8_t byte : buffer) {
         ss << byte;
         ss << std::endl;
      }

      std::cout << ss.str() << std::endl;

      gpio::sleep(std::chrono::seconds(1));
   }
   return 0;
}
