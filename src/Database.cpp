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
}

auto gpio::Database::stored_pins() -> std::unordered_map<uint16_t, BasePin*>&
{
   return m_stored_pins;
}
