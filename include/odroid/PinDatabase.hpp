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
   using uPtr = std::unique_ptr<PinDatabase>;
   using sPtr = std::shared_ptr<PinDatabase>;

   PinDatabase(const PinDatabase&) = delete;
   PinDatabase(PinDatabase&&) = delete;
   auto operator=(const PinDatabase&) -> PinDatabase& = delete;
   auto operator=(PinDatabase &&) -> PinDatabase& = delete;
   ~PinDatabase() = default;

   //   static auto get_pin(uint8_t pin_number) -> std::variant<digital::Pin, pwm::Pin>;
   //   auto contains(uint8_t pin_number) -> bool;

 private:
   explicit PinDatabase() = default;
   std::unordered_map<uint8_t, std::variant<digital::DigitalPin, pwm::PWMPin>> m_database;
};
} // namespace gpio

#endif // ODROIDGPIO_PINDATABASE_HPP
