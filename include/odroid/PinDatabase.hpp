#ifndef ODROIDGPIO_PINDATABASE_HPP
#define ODROIDGPIO_PINDATABASE_HPP

#include <nameof/nameof.hpp>
#include <odroid/BasePin.hpp>
#include <unordered_map>

namespace gpio {
class PinDatabase
{
 public:
   PinDatabase(const PinDatabase&) = delete;
   PinDatabase(PinDatabase&&) = delete;
   auto operator=(const PinDatabase&) -> PinDatabase& = delete;
   auto operator=(PinDatabase &&) -> PinDatabase& = delete;

   static auto instance() -> PinDatabase&;
   static auto contains(uint16_t pin_number) -> bool;
   static auto get(uint16_t pin_number) -> BasePin&;

   template <typename Pin, typename... Args>
   static auto make(uint16_t pin_number, Args&&... args) -> Pin&
   {
      auto& stored_data = instance().stored_data();
      auto* pin = new Pin(pin_number, args...);
      pin->type(nameof::nameof_type<std::decay_t<Pin>>());
      stored_data.emplace(std::make_pair(pin_number, std::move(pin)));
      return *pin;
   }

   template <typename Pin,
             typename... Args,
             typename std::enable_if_t<std::is_base_of_v<BasePin, std::decay_t<Pin>>, int> = 0>
   static auto get(uint16_t pin_number, Args&&... args) -> Pin&
   {
      auto& database = PinDatabase::instance();
      if (PinDatabase::contains(pin_number)) {
         auto& pin = gpio::PinDatabase::get(pin_number);
         if (nameof::nameof_type<std::decay_t<Pin>>() != pin.type()) {
            throw std::invalid_argument("Attempted to get pin that exists with incorrect type");
         }

         return static_cast<Pin&>(pin);
      }

      return database.make<Pin>(pin_number, args...);
   }

 private:
   auto stored_data() -> std::unordered_map<uint16_t, BasePin*>&;

   explicit PinDatabase() = default;
   ~PinDatabase();

   std::unordered_map<uint16_t, BasePin*> m_stored_data;
};
} // namespace gpio

#endif // ODROIDGPIO_PINDATABASE_HPP
