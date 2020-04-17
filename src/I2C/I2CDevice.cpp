#include "detail/I2C/I2C.hpp"

#include <iostream>
#include <odroid/I2C/I2CDevice.hpp>
#include <odroid/gpio.hpp>
#include <wiringPiI2C.h>


gpio::I2C::I2CDevice::I2CDevice(uint8_t device_number,
                                uint16_t sda_pin_number,
                                uint16_t scl_pin_number) :
   m_sda_pin(gpio::get<BasePin>(sda_pin_number)),
   m_scl_pin(gpio::get<BasePin>(scl_pin_number)),
   m_device_number(device_number),
   m_file_descriptor(gpio::I2C::open(m_device_number))
{}

auto gpio::I2C::I2CDevice::get(uint8_t device_number, uint16_t sda_pin, uint16_t scl_pin)
   -> gpio::I2C::I2CDevice&
{

   static I2CDevice device(device_number, sda_pin, scl_pin);
   return device;
}

auto gpio::I2C::I2CDevice::read_8_bits(uint32_t register_address) const -> uint8_t
{
   return gpio::I2C::read_8_bits(m_file_descriptor, register_address);
}

[[maybe_unused]] auto gpio::I2C::I2CDevice::read_16_bits(uint32_t register_address) const
   -> uint16_t
{
   return gpio::I2C::read_16_bits(m_file_descriptor, register_address);
}

void gpio::I2C::I2CDevice::write_8_bits(uint32_t register_address, uint8_t data)
{
   gpio::I2C::write_8_bits(m_file_descriptor, data, register_address);
}

[[maybe_unused]] void gpio::I2C::I2CDevice::write_16_bits(uint16_t data, uint32_t register_address)
{
   gpio::I2C::write_16_bits(m_file_descriptor, data, register_address);
}
