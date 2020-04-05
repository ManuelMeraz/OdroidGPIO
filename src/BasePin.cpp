#include <odroid/BasePin.hpp>
gpio::BasePin::BasePin(uint16_t pin_number) : m_pin_number(pin_number) {}

auto gpio::BasePin::pin_number() const -> uint16_t
{
   return m_pin_number;
}
