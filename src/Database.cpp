#include "odroid/Database.hpp"

#include <iostream>
#include <odroid/digital/DigitalPin.hpp>
#include <odroid/pwm/PWMPin.hpp>

auto gpio::Database::instance() -> gpio::Database&
{
   static Database database;
   return database;
}

gpio::Database::~Database()
{
   for (auto& [_, pin] : m_stored_pins) {
      (void)_; // silence warning for unused variable

      const auto type = pin->type();
      if (type == "gpio::pwm::PWMPin") {
         delete reinterpret_cast<gpio::pwm::PWMPin*>(pin);
      } else if (type == "gpio::digital::DigitalPin") {
         delete reinterpret_cast<gpio::digital::DigitalPin*>(pin);
      } else { // base pin
         delete pin;
      }
   }

   for (auto& [_, I2C_device] : m_stored_I2C_devices) {
      (void)_; // silence warning for unused variable
      delete I2C_device;
   }

   for (auto& [_, serial_port] : m_stored_serial_ports) {
      (void)_; // silence warning for unused variable
      delete serial_port;
   }
}

auto gpio::Database::stored_pins() -> std::unordered_map<uint16_t, BasePin*>&
{
   return m_stored_pins;
}

auto gpio::Database::stored_I2C_devices() -> std::unordered_map<uint16_t, gpio::I2C::I2CDevice*>&
{
   return m_stored_I2C_devices;
}

auto gpio::Database::stored_serial_ports()
   -> std::unordered_map<std::string, gpio::serial::SerialPort*>&
{
   return m_stored_serial_ports;
}
