#include "odroid/Database.hpp"

#include <iostream>
#include <odroid/digital/Pin.hpp>
#include <odroid/pwm/Pin.hpp>

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
      if (type == "gpio::pwm::Pin") {
         delete reinterpret_cast<gpio::pwm::Pin*>(pin);
      } else if (type == "gpio::digital::Pin") {
         delete reinterpret_cast<gpio::digital::Pin*>(pin);
      } else { // base pin
         delete pin;
      }
   }

   for (auto& [_, I2C_bus] : m_stored_I2C_buses) {
      (void)_; // silence warning for unused variable
      delete I2C_bus;
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

auto gpio::Database::stored_I2C_buses() -> std::unordered_map<uint16_t, gpio::I2C::Bus*>&
{
   return m_stored_I2C_buses;
}

auto gpio::Database::stored_serial_ports() -> std::unordered_map<std::string, gpio::serial::Port*>&
{
   return m_stored_serial_ports;
}
