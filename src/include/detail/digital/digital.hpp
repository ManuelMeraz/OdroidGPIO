#ifndef ODROIDGPIO_DIGITAL_HPP
#define ODROIDGPIO_DIGITAL_HPP

#include "odroid/digital/digital.hpp"

#include <cstdint>

namespace gpio::digital {
void write(uint8_t pin_number, digital::Write mode);
}


#endif // ODROIDGPIO_DIGITAL_HPP
