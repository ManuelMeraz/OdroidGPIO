#ifndef ODROIDGPIO_I2CDEVICE_HPP
#define ODROIDGPIO_I2CDEVICE_HPP

#include <odroid/BasePin.hpp>
#include <optional>
#include <wiringPiI2C.h>

namespace gpio::I2C {
class I2CDevice
{
 public:
   I2CDevice() = delete;
   I2CDevice(const I2CDevice&) = delete;
   I2CDevice(I2CDevice&&) = delete;
   auto operator=(const I2CDevice&) -> I2CDevice& = delete;
   auto operator=(I2CDevice &&) -> I2CDevice& = delete;
   ~I2CDevice() = default;

   [[nodiscard]] static auto get(std::optional<uint8_t> device_number,
                                 std::optional<uint16_t> sda_pin = 0,
                                 std::optional<uint16_t> scl_pin = 0) -> I2CDevice&;

   [[nodiscard]] auto read_8_bits(uint32_t register_address) const -> uint8_t;
   [[nodiscard]] auto read_16_bits(uint32_t register_address) const -> uint16_t;
   void write_8_bits(uint8_t data, uint32_t register_address);
   void write_16_bits(uint16_t data, uint32_t register_address);

   template <size_t num_bytes>
   [[nodiscard]] auto read(uint32_t register_address) const -> std::array<uint8_t, num_bytes>
   {
      std::array<uint8_t, num_bytes> buffer{};
      wiringPiI2CReadBlock(m_file_descriptor,
                           static_cast<int>(register_address),
                           &buffer[0],
                           static_cast<int>(num_bytes));
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
   explicit I2CDevice(uint8_t device_number,
                      uint16_t sda_pin_number = 0,
                      uint16_t scl_pin_number = 0);

   BasePin& m_sda_pin;
   BasePin& m_scl_pin;
   uint8_t m_device_number{};
   int m_file_descriptor{};
};
} // namespace gpio::I2C

#endif // ODROIDGPIO_I2CDEVICE_HPP
