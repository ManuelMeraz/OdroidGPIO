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

auto gpio::PinDatabase::contains(uint8_t pin_number) -> bool
{
   auto& stored_data = g_database->m_database;
   return stored_data.find(pin_number) != stored_data.end();
}

auto gpio::PinDatabase::emplace(std::pair<uint8_t, std::unique_ptr<BasePin>>&& data) -> void
{
   auto& stored_data = g_database->m_database;
   stored_data.emplace(std::move(data));
}
