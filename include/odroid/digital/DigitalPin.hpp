#ifndef ODROIDGPIO_DIGITAL_PIN_HPP
#define ODROIDGPIO_DIGITAL_PIN_HPP

#include "odroid/digital/digital.hpp"

#include <cstdint>
#include <memory>
#include <odroid/BasePin.hpp>
#include <odroid/PinDatabase.hpp>

namespace gpio::digital {
class DigitalPin final : public BasePin
{
 public:
   DigitalPin() = delete;
   DigitalPin(const DigitalPin&) = delete;
   DigitalPin(DigitalPin&&) = delete;
   auto operator=(const DigitalPin&) -> DigitalPin& = delete;
   auto operator=(DigitalPin &&) -> DigitalPin& = delete;

   [[nodiscard]] auto mode() const -> Mode;
   void mode(Mode mode);

   [[nodiscard]] auto read() const -> IO;
   void write(IO mode);

 private:
   friend class ::gpio::PinDatabase;

   explicit DigitalPin(uint16_t pin_number, Mode mode = Mode::OUTPUT);
   ~DigitalPin();

   Mode m_mode{};
};
} // namespace gpio::digital

#endif // ODROIDGPIO_DIGITAL_PIN_HPP
