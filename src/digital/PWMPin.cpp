
#include <detail/gpio.hpp>
#include <odroid/digital/DigitalPin.hpp>
#include <wiringPi.h>

gpio::digital::DigitalPin::DigitalPin(uint8_t pin_number, Mode mode) :
   BasePin(pin_number), m_mode(mode)
{
   gpio::pin_mode(m_pin_number, static_cast<uint8_t>(m_mode));
}

gpio::digital::DigitalPin::~DigitalPin()
{
   gpio::pin_mode(m_pin_number, static_cast<uint8_t>(Mode::OFF));
}

auto gpio::digital::DigitalPin::mode() const -> Mode
{
   return m_mode;
}

void gpio::digital::DigitalPin::mode(Mode mode)
{
   m_mode = mode;
   gpio::pin_mode(m_pin_number, static_cast<uint8_t>(m_mode));
}

void gpio::digital::DigitalPin::write(Write mode)
{
   digitalWrite(m_pin_number, static_cast<int>(mode));
}
