#ifndef DETAIL_ODROIDGPIO_SERIAL_HPP
#define DETAIL_ODROIDGPIO_SERIAL_HPP

#include <cstdint>
#include <string>

namespace gpio::serial {
auto open(const std::string& device, uint32_t baud_rate) -> int;
void close(int file_descriptor);
void clear(int file_descriptor);
void write_byte(int file_descriptor, uint8_t byte);
void write(int file_descriptor, const std::string& message);
auto read_char(int file_descriptor) -> char;
void print(int file_descriptor, const std::string& message);
auto data_available(int file_descriptor) -> bool;
} // namespace gpio::serial

#endif // DETAIL_ODROIDGPIO_SERIAL_HPP
