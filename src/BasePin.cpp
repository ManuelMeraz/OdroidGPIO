#include <odroid/BasePin.hpp>
#include <string>

gpio::BasePin::BasePin(uint16_t pin_number) : m_pin_number(pin_number) {}

auto gpio::BasePin::pin_number() const -> uint16_t
{
   return m_pin_number;
}

auto gpio::BasePin::type() -> std::string_view
{
   return m_type;
}

void gpio::BasePin::type(std::string_view type)
{
   m_type = type.data();
}
