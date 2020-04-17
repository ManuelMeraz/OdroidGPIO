#ifndef ODROIDGPIO_PWM_PIN_HPP
#define ODROIDGPIO_PWM_PIN_HPP

#include "odroid/pwm/pwm.hpp"

#include <cstdint>
#include <memory>
#include <odroid/BasePin.hpp>
#include <odroid/Database.hpp>

namespace gpio::pwm {
class PWMPin final : public BasePin
{
   friend class ::gpio::Database;

 public:
   PWMPin() = delete;
   PWMPin(const PWMPin&) = delete;
   PWMPin(PWMPin&&) = delete;
   auto operator=(const PWMPin&) -> PWMPin& = delete;
   auto operator=(PWMPin &&) -> PWMPin& = delete;

   [[nodiscard]] auto mode() const -> Mode;
   void mode(Mode mode);

   [[nodiscard]] auto duty_cycle() const -> uint16_t;
   void duty_cycle(uint16_t duty_cycle);

 private:
   explicit PWMPin(uint16_t pin_number, Mode mode = Mode::OUTPUT);
   ~PWMPin();

   uint16_t m_duty_cycle{};
   Mode m_mode{};
};
} // namespace gpio::pwm
#endif // ODROIDGPIO_PWM_PIN_HPP
