
#include <detail/digital/digital.hpp>
#include <detail/gpio.hpp>
#include <odroid/digital/DigitalPin.hpp>
#include <odroid/gpio.hpp>
#include <wiringPi.h>

gpio::digital::DigitalPin::DigitalPin(uint16_t pin_number, Mode mode) :
   BasePin(pin_number), m_mode(mode)
{
   if (!gpio::setup()) {
      throw std::runtime_error("Failed to initialize gpio");
   }

   gpio::pin_mode(m_pin_number, static_cast<uint16_t>(m_mode));
}

gpio::digital::DigitalPin::~DigitalPin()
{
   gpio::pin_mode(m_pin_number, static_cast<uint16_t>(Mode::OFF));
}

auto gpio::digital::DigitalPin::mode() const -> Mode
{
   return m_mode;
}

void gpio::digital::DigitalPin::mode(Mode mode)
{
   m_mode = mode;
   gpio::pin_mode(m_pin_number, static_cast<uint16_t>(m_mode));
}

auto gpio::digital::DigitalPin::read() const -> gpio::digital::IO
{
   return gpio::digital::read(m_pin_number);
}

void gpio::digital::DigitalPin::write(IO mode)
{
   gpio::digital::write(m_pin_number, mode);
}
