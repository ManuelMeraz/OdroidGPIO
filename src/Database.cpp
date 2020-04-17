#include "odroid/Database.hpp"

auto gpio::Database::instance() -> gpio::Database&
{
   static Database database;
   return database;
}

auto gpio::Database::contains(uint16_t pin_number) -> bool
{
   auto& data = instance().stored_pins();
   return data.find(pin_number) != data.end();
}

auto gpio::Database::get(uint16_t pin_number) -> gpio::BasePin&
{
   auto& data = instance().stored_pins();
   return *data.at(pin_number);
}

gpio::Database::~Database()
{
   for (auto& [_, pin] : m_stored_pins) {
      (void)_; // silence warning for unused variable
      delete pin;
   }
}

auto gpio::Database::stored_pins() -> std::unordered_map<uint16_t, BasePin*>&
{
   return m_stored_pins;
}
