#include "odroid/PinDatabase.hpp"

#include <odroid/pwm/PWMPin.hpp>
namespace {
struct PinDatabaseDeleter
{
   void operator()(gpio::PinDatabase* database) const
   {
      delete database;
   }
};

// globals
std::unique_ptr<gpio::PinDatabase, PinDatabaseDeleter> g_database{nullptr};
} // namespace

auto gpio::PinDatabase::instance() -> gpio::PinDatabase&
{
   if (g_database == nullptr) {
      g_database.reset(new gpio::PinDatabase());
   }

   return *g_database;
}

auto gpio::PinDatabase::contains(uint8_t pin_number) -> bool
{
   auto& stored_data = g_database->m_database;
   return stored_data.find(pin_number) != stored_data.end();
}

auto gpio::PinDatabase::get(uint8_t pin_number) -> gpio::BasePin&
{
   auto& stored_data = g_database->m_database;
   return *stored_data.at(pin_number);
}

gpio::PinDatabase::~PinDatabase()
{
   uint8_t pin_number{};
   for (auto& [_, pin] : m_database) {
      pin_number = _;
      delete pin;
   }
   m_database.erase(pin_number);
}
