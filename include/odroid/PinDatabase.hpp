#ifndef ODROIDGPIO_PINDATABASE_HPP
#define ODROIDGPIO_PINDATABASE_HPP

#include <memory>
#include <odroid/BasePin.hpp>
#include <unordered_map>
#include <variant>

namespace gpio {
class PinDatabase
{
 public:
   PinDatabase(const PinDatabase&) = delete;
   PinDatabase(PinDatabase&&) = delete;
   auto operator=(const PinDatabase&) -> PinDatabase& = delete;
   auto operator=(PinDatabase &&) -> PinDatabase& = delete;
   ~PinDatabase();

   static auto instance() -> PinDatabase&;
   auto contains(uint8_t pin_number) -> bool;
   auto get(uint8_t pin_number) -> BasePin&;

   template <typename Pin, typename... Args>
   auto make(uint8_t pin_number, Args&&... args) -> Pin&
   {
      auto& stored_data = m_database;
      auto* pin = new Pin(pin_number, args...);
      stored_data.emplace(std::make_pair(pin_number, std::move(pin)));
      return *pin;
   }

   template <typename Pin,
             typename... Args,
             typename std::enable_if_t<std::is_base_of_v<BasePin, std::decay_t<Pin>>, int> = 0>
   static auto get(uint8_t pin_number, Args&&... args) -> Pin&
   {
      auto& database = PinDatabase::instance();
      if (database.contains(pin_number)) {
         return static_cast<Pin&>(database.get(pin_number));
      }

      return database.make<Pin>(pin_number, args...);
   }

 private:
   explicit PinDatabase() = default;
   std::unordered_map<uint8_t, BasePin*> m_database;
};
} // namespace gpio

#endif // ODROIDGPIO_PINDATABASE_HPP
