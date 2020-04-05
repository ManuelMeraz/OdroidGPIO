#ifndef ODROIDGPIO_PWM_PIN_HPP
#define ODROIDGPIO_PWM_PIN_HPP

#include "odroid/pwm/pwm.hpp"

#include <cstdint>
#include <memory>
#include <odroid/BasePin.hpp>

namespace gpio::pwm {
class Pin : public BasePin
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

   [[nodiscard]] auto duty_cycle() const -> uint8_t;
   void duty_cycle(uint8_t duty_cycle);

 private:
   uint8_t m_pin_number{};
   uint8_t m_duty_cycle{};

   Mode m_mode{};
};
} // namespace gpio::pwm
#endif // ODROIDGPIO_PWM_PIN_HPP
