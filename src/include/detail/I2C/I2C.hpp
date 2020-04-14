#ifndef DETAIL_ODROIDGPIO_I2C_HPP
#define DETAIL_ODROIDGPIO_I2C_HPP

#include <array>
#include <cstdint>
#include <string>

namespace gpio::I2C {
auto open(uint8_t device_number) -> int;
auto read(int file_descriptor) -> uint32_t;
auto read_8_bits(int file_descriptor, uint8_t register_address) -> uint8_t;
auto read_16_bits(int file_descriptor, uint32_t register_address) -> uint16_t;
auto write(int file_descriptor, uint32_t data) -> uint32_t;
auto write_8_bits(int file_descriptor, uint8_t data, uint32_t register_address) -> uint32_t;
auto write_16_bits(int file_descriptor, uint16_t data, uint32_t register_address) -> uint32_t;
} // namespace gpio::I2C

#endif // DETAIL_ODROIDGPIO_I2C_HPP
