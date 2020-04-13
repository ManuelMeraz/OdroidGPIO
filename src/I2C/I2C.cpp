#include "detail/I2C/I2C.hpp"

#include <sstream>
#include <wiringPiI2C.h>

auto gpio::I2C::open(uint8_t device_number) -> int
{

   const int file_descriptor = wiringPiI2CSetup(device_number);
   if (file_descriptor == -1) {
      std::stringstream ss;
      ss << "Failed to open I2C device number. Device: " << device_number << std::endl;
      throw std::runtime_error(ss.str());
   }

   return file_descriptor;
}

void gpio::I2C::write(const int file_descriptor, const uint32_t data)
{
   wiringPiI2CWrite(file_descriptor, static_cast<int>(data));
}

auto gpio::I2C::read(int file_descriptor) -> uint32_t
{
   return static_cast<uint32_t>(wiringPiI2CRead(file_descriptor));
}
