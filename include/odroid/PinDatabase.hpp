#ifndef ODROIDGPIO_PINDATABASE_HPP
#define ODROIDGPIO_PINDATABASE_HPP

#include <memory>
#include <odroid/digital/DigitalPin.hpp>
#include <odroid/pwm/PWMPin.hpp>
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
   ~PinDatabase() = default;

   static auto contains(uint8_t pin_number) -> bool;

   static auto emplace(std::pair<uint8_t, std::unique_ptr<BasePin>>&& data) -> void;
   static auto get(uint8_t pin_number) -> BasePin&;

   template <typename Pin,
             typename... Args,
             typename std::enable_if_t<std::is_base_of_v<BasePin, std::decay_t<Pin>>, int> = 0>
   static auto get(uint8_t pin_number, Args&&... args) -> Pin&
   {
      if (PinDatabase::contains(pin_number)) {
         return static_cast<Pin>(PinDatabase::get(pin_number));
      }

      const auto pin = std::make_unique<Pin>(pin_number, args...);
      PinDatabase::emplace(std::make_pair(pin_number, std::move(pin)));
      return *pin;
   }

 private:
   explicit PinDatabase() = default;
   std::unordered_map<uint8_t, std::unique_ptr<BasePin>> m_database;
};
} // namespace gpio

#endif // ODROIDGPIO_PINDATABASE_HPP
