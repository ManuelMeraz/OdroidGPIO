#include "detail/I2C/I2C.hpp"

#include <sstream>
#include <wiringPiI2C.h>

auto gpio::I2C::open(uint8_t device_number) -> int
{

   const int file_descriptor = wiringPiI2CSetup(device_number);
   if (file_descriptor == -1) {
      std::stringstream ss;
      ss << "Failed to open I2C device number. Bus: " << device_number << std::endl;
      throw std::runtime_error(ss.str());
   }

   return file_descriptor;
}

auto gpio::I2C::read(int file_descriptor) -> uint32_t
{
   return static_cast<uint32_t>(wiringPiI2CRead(file_descriptor));
}

auto gpio::I2C::read_8_bits(int file_descriptor, uint8_t register_address) -> uint8_t
{
   return static_cast<uint8_t>(
      wiringPiI2CReadReg8(file_descriptor, static_cast<int>(register_address)));
}

auto gpio::I2C::read_16_bits(int file_descriptor, uint32_t register_address) -> uint16_t
{
   return static_cast<uint16_t>(
      wiringPiI2CReadReg16(file_descriptor, static_cast<int>(register_address)));
}

auto gpio::I2C::write(const int file_descriptor, const uint32_t data) -> uint32_t
{
   return static_cast<uint32_t>(wiringPiI2CWrite(file_descriptor, static_cast<int>(data)));
}

auto gpio::I2C::write_8_bits(int file_descriptor, uint8_t data, uint32_t register_address)
   -> uint32_t
{
   return static_cast<uint32_t>(
      wiringPiI2CWriteReg8(file_descriptor, static_cast<int>(register_address), data));
}

auto gpio::I2C::write_16_bits(int file_descriptor, uint16_t data, uint32_t register_address)
   -> uint32_t
{
   return static_cast<uint32_t>(
      wiringPiI2CWriteReg16(file_descriptor, static_cast<int>(register_address), data));
}
