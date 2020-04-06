#ifndef DETAIL_ODROIDGPIO_SERIAL_HPP
#define DETAIL_ODROIDGPIO_SERIAL_HPP

#include <cstdint>
#include <string>

namespace gpio::serial {
int open(const std::string& device, uint32_t baud_rate);
void close(const int file_descriptor);
void clear(const int file_descriptor);
void write_byte(const int file_descriptor, const uint8_t byte);
void write(const int file_descriptor, const std::string& message);
void print(const int file_descriptor, const std::string& message);
uint32_t data_available(const int file_descriptor);
} // namespace gpio::serial

#endif // DETAIL_ODROIDGPIO_SERIAL_HPP
