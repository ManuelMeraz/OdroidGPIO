#ifndef ODROIDGPIO_I2CDEVICE_HPP
#define ODROIDGPIO_I2CDEVICE_HPP

#include <odroid/BasePin.hpp>
#include <optional>

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

   [[nodiscard]] static auto get(std::optional<uint16_t> sda_pin = std::nullopt,
                                 std::optional<uint16_t> scl_pin = std::nullopt,
                                 std::optional<uint8_t> device_number = std::nullopt) -> I2CDevice&;

   [[nodiscard]] auto read() const -> uint32_t;
   void write(uint32_t data);

 private:
   explicit I2CDevice(uint16_t sda_pin_number, uint16_t scl_pin_number, uint8_t device_number);

   BasePin& m_sda_pin;
   BasePin& m_scl_pin;
   uint8_t m_device_number{};
   int m_file_descriptor{};
};
} // namespace gpio::I2C

#endif // ODROIDGPIO_I2CDEVICE_HPP
