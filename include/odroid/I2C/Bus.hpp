#ifndef ODROIDGPIO_BUS_HPP
#define ODROIDGPIO_BUS_HPP

#include <odroid/BasePin.hpp>
#include <optional>
#include <wiringPiI2C.h>

namespace gpio {
class Database;
} // namespace gpio

namespace gpio::I2C {
class Bus
{
   friend class gpio::Database;

 public:
   Bus() = delete;
   Bus(const Bus&) = delete;
   Bus(Bus&&) = delete;
   auto operator=(const Bus&) -> Bus& = delete;
   auto operator=(Bus &&) -> Bus& = delete;

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
   explicit Bus(uint8_t device_number, uint16_t sda_pin_number = 0, uint16_t scl_pin_number = 0);
   ~Bus() = default;

   BasePin& m_sda_pin;
   BasePin& m_scl_pin;
   uint8_t m_device_number{};
   int m_file_descriptor{};
};
} // namespace gpio::I2C

#endif // ODROIDGPIO_BUS_HPP
