#ifndef ODROIDGPIO_DIGITAL_PIN_HPP
#define ODROIDGPIO_DIGITAL_PIN_HPP

#include "odroid/digital/digital.hpp"

#include <cstdint>
#include <memory>

namespace gpio::digital {
class Pin
{
 public:
   using uPtr = std::unique_ptr<Pin>;
   using sPtr = std::shared_ptr<Pin>;

   Pin() = delete;
   Pin(const Pin&) = delete;
   Pin(Pin&&) = delete;
   auto operator=(const Pin&) -> Pin& = delete;
   auto operator=(Pin &&) -> Pin& = delete;

   explicit Pin(uint8_t pin_number, Mode mode = Mode::OUTPUT);
   ~Pin();

   [[nodiscard]] auto mode() const -> Mode;
   void mode(Mode mode);
   void write(Write mode);

 private:
   uint8_t m_pin_number{};
   Mode m_mode{};
};
} // namespace gpio::digital

#endif // ODROIDGPIO_DIGITAL_PIN_HPP
