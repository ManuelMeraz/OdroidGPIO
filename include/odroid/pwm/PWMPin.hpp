#ifndef ODROIDGPIO_PWM_PIN_HPP
#define ODROIDGPIO_PWM_PIN_HPP

#include "odroid/pwm/pwm.hpp"

#include <cstdint>
#include <memory>
#include <odroid/BasePin.hpp>

namespace gpio::pwm {
class PWMPin final : public BasePin
{
 public:
   using uPtr = std::unique_ptr<PWMPin>;
   using sPtr = std::shared_ptr<PWMPin>;

   PWMPin() = delete;
   PWMPin(const PWMPin&) = delete;
   PWMPin(PWMPin&&) = delete;
   auto operator=(const PWMPin&) -> PWMPin& = delete;
   auto operator=(PWMPin &&) -> PWMPin& = delete;
   ~PWMPin();

   [[nodiscard]] auto mode() const -> Mode;
   void mode(Mode mode);

   [[nodiscard]] auto duty_cycle() const -> uint8_t;
   void duty_cycle(uint8_t duty_cycle);

 private:
   friend class PinDatabase;

   explicit PWMPin(uint8_t pin_number, Mode mode = Mode::OUTPUT);
   uint8_t m_pin_number{};
   uint8_t m_duty_cycle{};

   Mode m_mode{};
};
} // namespace gpio::pwm
#endif // ODROIDGPIO_PWM_PIN_HPP
