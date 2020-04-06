#ifndef DETAIL_ODROIDGPIO_DIGITAL_HPP
#define DETAIL_ODROIDGPIO_DIGITAL_HPP

#include "odroid/digital/digital.hpp"

#include <cstdint>

namespace gpio::digital {
void write(uint16_t pin_number, digital::IO mode);
digital::IO read(uint16_t pin_number);
} // namespace gpio::digital

#endif // DETAIL_ODROIDGPIO_DIGITAL_HPP
