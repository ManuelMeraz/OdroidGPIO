#ifndef ODROIDGPIO_DIGITAL_PIN_HPP
#define ODROIDGPIO_DIGITAL_PIN_HPP

#include "odroid/digital/digital.hpp"

#include <cstdint>
#include <memory>
#include <odroid/BasePin.hpp>

namespace gpio {
class Database;
}

namespace gpio::digital {
class Pin final : public BasePin
{
   friend class gpio::Database;

 public:
   Pin() = delete;
   Pin(const Pin&) = delete;
   Pin(Pin&&) = delete;
   auto operator=(const Pin&) -> Pin& = delete;
   auto operator=(Pin &&) -> Pin& = delete;

   [[nodiscard]] auto mode() const -> Mode;
   void mode(Mode mode);

   [[nodiscard]] auto read() const -> IO;
   void write(IO mode);

 private:
   explicit Pin(uint16_t pin_number, Mode mode = Mode::OUTPUT);
   ~Pin();

   Mode m_mode{};
};
} // namespace gpio::digital

#endif // ODROIDGPIO_DIGITAL_PIN_HPP
