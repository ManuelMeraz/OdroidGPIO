#include "detail/I2C/I2C.hpp"

#include <iostream>
#include <odroid/I2C/I2CDevice.hpp>
#include <odroid/gpio.hpp>
#include <sstream>
#include <utility>

namespace {
struct I2CDeviceDeleter
{
   void operator()(gpio::I2C::I2CDevice* I2C_device) const
   {
      delete I2C_device;
   }
};

// globals
std::unique_ptr<gpio::I2C::I2CDevice, I2CDeviceDeleter> g_I2C_device{nullptr};
} // namespace

gpio::I2C::I2CDevice::I2CDevice(uint16_t sda_pin_number,
                                uint16_t scl_pin_number,
                                uint8_t device_number) :
   m_sda_pin(gpio::get<BasePin>(sda_pin_number)),
   m_scl_pin(gpio::get<BasePin>(scl_pin_number)),
   m_device_number(device_number),
   m_file_descriptor(gpio::I2C::open(m_device_number))
{}

auto gpio::I2C::I2CDevice::get(std::optional<uint16_t> sda_pin,
                               std::optional<uint16_t> scl_pin,
                               std::optional<uint8_t> device_number) -> gpio::I2C::I2CDevice&
{
   if (g_I2C_device == nullptr) {
      if (!sda_pin || !scl_pin || !device_number) {
         if (!sda_pin) {
            std::cerr << "Missing sda pin from argument" << std::endl;
         }

         if (!scl_pin) {
            std::cerr << "Missing scl pin from argument" << std::endl;
         }

         if (!device_number) {
            std::cerr << "Missing device name from argument" << std::endl;
         }

         throw std::invalid_argument("Need sda pin, scl pin, and device name to get I2C device");
      }

      g_I2C_device.reset(new gpio::I2C::I2CDevice(*sda_pin, *scl_pin, *device_number));
   }

   return *g_I2C_device;
}

auto gpio::I2C::I2CDevice::read() const -> uint32_t
{
   return gpio::I2C::read(m_file_descriptor);
}

void gpio::I2C::I2CDevice::write(const uint32_t data)
{
   gpio::I2C::write(m_file_descriptor, data);
}
