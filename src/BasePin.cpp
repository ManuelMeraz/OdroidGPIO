#include <odroid/BasePin.hpp>
gpio::BasePin::BasePin(uint8_t pin_number) : m_pin_number(pin_number) {}

auto gpio::BasePin::pin_number() -> uint8_t
{
   return m_pin_number;
}
