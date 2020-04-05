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

// auto gpio::PinDatabase::get_pin(uint8_t pin_number) -> std::variant<gpio::digital::Pin,
// gpio::pwm::Pin>
//{
////   auto& database = *g_database;
////   if(database.contains(pin_number)) {
////      return database.m_database.at(pin_number);
////   }
//   return std::variant<gpio::digital::Pin, gpio::pwm::Pin>();
//}

// auto gpio::PinDatabase::contains(uint8_t pin_number) -> bool
//{
//   return m_database.find(pin_number) != m_database.end();
//}
