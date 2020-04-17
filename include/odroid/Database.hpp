#ifndef ODROIDGPIO_DATABASE_HPP
#define ODROIDGPIO_DATABASE_HPP

#include <nameof/nameof.hpp>
#include <odroid/BasePin.hpp>
#include <unordered_map>

namespace gpio {
class Database
{
 public:
   Database(const Database&) = delete;
   Database(Database&&) = delete;
   auto operator=(const Database&) -> Database& = delete;
   auto operator=(Database &&) -> Database& = delete;

   static auto instance() -> Database&;
   static auto contains(uint16_t pin_number) -> bool;
   static auto get(uint16_t pin_number) -> BasePin&;

   template <typename Pin,
             typename... Args,
             typename std::enable_if_t<std::is_base_of_v<BasePin, std::decay_t<Pin>>, int> = 0>
   static auto get(uint16_t pin_number, Args&&... args) -> Pin&
   {
      auto& database = Database::instance();
      if (Database::contains(pin_number)) {
         auto& pin = gpio::Database::get(pin_number);
         if (nameof::nameof_type<std::decay_t<Pin>>() != pin.type()) {
            throw std::invalid_argument("Attempted to get pin that exists with incorrect type");
         }

         return static_cast<Pin&>(pin);
      }

      return database.make_pin<Pin>(pin_number, args...);
   }

 private:
   explicit Database() = default;
   ~Database();

   auto stored_pins() -> std::unordered_map<uint16_t, BasePin*>&;

   template <typename Pin,
             typename... Args,
             typename std::enable_if_t<std::is_base_of_v<BasePin, std::decay_t<Pin>>, int> = 0>
   static auto make_pin(uint16_t pin_number, Args&&... args) -> Pin&
   {
      auto& stored_pins = instance().stored_pins();
      auto* pin = new Pin(pin_number, args...);
      pin->type(nameof::nameof_type<std::decay_t<Pin>>());
      stored_pins.emplace(std::make_pair(pin_number, std::move(pin)));
      return *pin;
   }

   std::unordered_map<uint16_t, BasePin*> m_stored_pins;
};
} // namespace gpio

#endif // ODROIDGPIO_DATABASE_HPP
