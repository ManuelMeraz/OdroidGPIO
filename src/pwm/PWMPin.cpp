#include <detail/gpio.hpp>
#include <detail/pwm/pwm.hpp>
#include <odroid/pwm/PWMPin.hpp>

gpio::pwm::PWMPin::PWMPin(uint16_t pin_number, Mode mode) : BasePin(pin_number), m_mode(mode)
{
   gpio::pin_mode(pin_number, static_cast<uint16_t>(m_mode));
   duty_cycle(0);
}

gpio::pwm::PWMPin::~PWMPin()
{
   duty_cycle(0);
   gpio::pin_mode(m_pin_number, static_cast<uint16_t>(Mode::OFF));
}

auto gpio::pwm::PWMPin::mode() const -> Mode
{
   return m_mode;
}

void gpio::pwm::PWMPin::mode(Mode mode)
{
   m_mode = mode;
   gpio::pin_mode(m_pin_number, static_cast<uint16_t>(m_mode));
}

auto gpio::pwm::PWMPin::duty_cycle() const -> uint16_t
{
   return m_duty_cycle;
}

void gpio::pwm::PWMPin::duty_cycle(uint16_t duty_cycle)
{
   if (duty_cycle > 100) {
      throw std::invalid_argument("Duty cycle must be: [0, 100]");
   }

   m_duty_cycle = duty_cycle;
   gpio::pwm::duty_cycle(m_pin_number, duty_cycle);
}
