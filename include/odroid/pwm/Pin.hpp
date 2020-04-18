#ifndef ODROIDGPIO_PWM_PIN_HPP
#define ODROIDGPIO_PWM_PIN_HPP

#include "odroid/pwm/pwm.hpp"

#include <cstdint>
#include <memory>
#include <odroid/BasePin.hpp>

namespace gpio {
class Database;
} // namespace gpio

namespace gpio::pwm {
class Pin final : public BasePin
{
   friend class ::gpio::Database;

 public:
   Pin() = delete;
   Pin(const Pin&) = delete;
   Pin(Pin&&) = delete;
   auto operator=(const Pin&) -> Pin& = delete;
   auto operator=(Pin &&) -> Pin& = delete;

   [[nodiscard]] auto mode() const -> Mode;
   void mode(Mode mode);

   [[nodiscard]] auto duty_cycle() const -> uint16_t;
   void duty_cycle(uint16_t duty_cycle);

 private:
   explicit Pin(uint16_t pin_number, Mode mode = Mode::OUTPUT);
   ~Pin();

   uint16_t m_duty_cycle{};
   Mode m_mode{};
};
} // namespace gpio::pwm
#endif // ODROIDGPIO_PWM_PIN_HPP
