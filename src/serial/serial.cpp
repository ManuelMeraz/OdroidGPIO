#include "detail/serial/serial.hpp"

int gpio::serial::open(const std::string& device, uint32_t baud_rate)
{
   return 0;
}
void gpio::serial::close(const int file_descriptor) {}
void gpio::serial::clear(const int file_descriptor) {}
void gpio::serial::write_byte(const int file_descriptor, const uint8_t byte) {}
void gpio::serial::write(const int file_descriptor, const std::string& message) {}
void gpio::serial::print(const int file_descriptor, const std::string& message) {}
