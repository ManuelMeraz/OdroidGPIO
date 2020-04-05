#ifndef ODROIDGPIO_DIGITAL_PIN_HPP
#define ODROIDGPIO_DIGITAL_PIN_HPP

#include "odroid/digital/digital.hpp"

#include <cstdint>
#include <memory>

namespace gpio::digital {
class DigitalPin
{
 public:
   using uPtr = std::unique_ptr<DigitalPin>;
   using sPtr = std::shared_ptr<DigitalPin>;

   DigitalPin() = delete;
   DigitalPin(const DigitalPin&) = delete;
   DigitalPin(DigitalPin&&) = delete;
   auto operator=(const DigitalPin&) -> DigitalPin& = delete;
   auto operator=(DigitalPin &&) -> DigitalPin& = delete;

   ~DigitalPin();

   [[nodiscard]] auto mode() const -> Mode;
   void mode(Mode mode);
   void write(Write mode);

 private:
   friend class PinDatabase;

   explicit DigitalPin(uint8_t pin_number, Mode mode = Mode::OUTPUT);
   uint8_t m_pin_number{};
   Mode m_mode{};
};
} // namespace gpio::digital

#endif // ODROIDGPIO_DIGITAL_PIN_HPP
