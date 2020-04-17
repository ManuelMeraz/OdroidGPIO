#include "odroid/PinDatabase.hpp"

auto gpio::PinDatabase::instance() -> gpio::PinDatabase&
{
   static PinDatabase database;
   return database;
}

auto gpio::PinDatabase::contains(uint16_t pin_number) -> bool
{
   auto& data = instance().stored_data();
   return data.find(pin_number) != data.end();
}

auto gpio::PinDatabase::get(uint16_t pin_number) -> gpio::BasePin&
{
   auto& data = instance().stored_data();
   return *data.at(pin_number);
}

gpio::PinDatabase::~PinDatabase()
{
   for (auto& [_, pin] : m_stored_data) {
      (void)_; // silence warning for unused variable
      delete pin;
   }
}

auto gpio::PinDatabase::stored_data() -> std::unordered_map<uint16_t, BasePin*>&
{
   return m_stored_data;
}
