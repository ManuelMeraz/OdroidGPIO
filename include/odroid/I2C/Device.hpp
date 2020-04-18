#ifndef ODROIDGPIO_DEVICE_HPP
#define ODROIDGPIO_DEVICE_HPP

#include <odroid/BasePin.hpp>
#include <optional>
#include <wiringPiI2C.h>

namespace gpio {
class Database;
} // namespace gpio

namespace gpio::I2C {
class Device
{
   friend class gpio::Database;

 public:
   Device() = delete;
   Device(const Device&) = delete;
   Device(Device&&) = delete;
   auto operator=(const Device&) -> Device& = delete;
   auto operator=(Device &&) -> Device& = delete;

   [[nodiscard]] auto read_8_bits(uint32_t register_address) const -> uint8_t;
   [[maybe_unused]] [[nodiscard]] auto read_16_bits(uint32_t register_address) const -> uint16_t;
   void write_8_bits(uint32_t register_address, uint8_t data);
   [[maybe_unused]] void write_16_bits(uint16_t data, uint32_t register_address);

   template <size_t NumBytes>
   [[nodiscard]] auto read(uint32_t register_address) const -> std::array<uint8_t, NumBytes>
   {
      std::array<uint8_t, NumBytes> buffer{};
      wiringPiI2CReadBlock(m_file_descriptor,
                           static_cast<int>(register_address),
                           &buffer[0],
                           static_cast<int>(NumBytes));
      return buffer;
   }

   template <size_t num_bytes>
   void write(std::array<uint8_t, num_bytes>& buffer, uint32_t register_address)
   {
      wiringPiI2CReadBlock(m_file_descriptor,
                           static_cast<int>(register_address),
                           static_cast<uint8_t*>(&buffer[0]),
                           static_cast<int>(num_bytes));
   }

 private:
   explicit Device(uint8_t device_number, uint16_t sda_pin_number = 0, uint16_t scl_pin_number = 0);
   ~Device() = default;

   BasePin& m_sda_pin;
   BasePin& m_scl_pin;
   uint8_t m_device_number{};
   int m_file_descriptor{};
};
} // namespace gpio::I2C

#endif // ODROIDGPIO_DEVICE_HPP
