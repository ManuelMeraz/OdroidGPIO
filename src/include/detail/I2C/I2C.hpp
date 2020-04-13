#ifndef DETAIL_ODROIDGPIO_I2C_HPP
#define DETAIL_ODROIDGPIO_I2C_HPP

#include <cstdint>
#include <string>

namespace gpio::I2C {
auto open(uint8_t device_number) -> int;
void write(int file_descriptor, uint32_t data);
auto read(int file_descriptor) -> uint32_t;
} // namespace gpio::I2C

#endif // DETAIL_ODROIDGPIO_I2C_HPP
