#include <detail/gpio.hpp>
#include <detail/pwm/pwm.hpp>
#include <iostream>
#include <odroid/gpio.hpp>
#include <odroid/pwm/Pin.hpp>

gpio::pwm::Pin::Pin(uint16_t pin_number, Mode mode) : BasePin(pin_number), m_mode(mode)
{
   if (!gpio::setup()) {
      throw std::runtime_error("Failed to initialize gpio");
   }

   gpio::pin_mode(pin_number, static_cast<uint16_t>(m_mode));
   duty_cycle(0);
}

gpio::pwm::Pin::~Pin()
{
   duty_cycle(0);
   gpio::pin_mode(m_pin_number, static_cast<uint16_t>(Mode::OFF));
}

auto gpio::pwm::Pin::mode() const -> Mode
{
   return m_mode;
}

void gpio::pwm::Pin::mode(Mode mode)
{
   m_mode = mode;
   gpio::pin_mode(m_pin_number, static_cast<uint16_t>(m_mode));
}

auto gpio::pwm::Pin::duty_cycle() const -> uint16_t
{
   return m_duty_cycle;
}

void gpio::pwm::Pin::duty_cycle(uint16_t duty_cycle)
{
   if (duty_cycle > 100) {
      std::cerr << "[WARNING] Duty cycle greater than 100. Setting to 100." << std::endl;
      duty_cycle = 100;
   }

   m_duty_cycle = duty_cycle;
   gpio::pwm::duty_cycle(m_pin_number, duty_cycle);
}
