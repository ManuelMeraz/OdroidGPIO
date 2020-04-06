#ifndef ODROIDGPIO_SERIALPORT_HPP
#define ODROIDGPIO_SERIALPORT_HPP

#include <odroid/BasePin.hpp>

namespace gpio::serial {
class SerialPort
{
 public:
   SerialPort() = delete;
   SerialPort(const SerialPort&) = delete;
   SerialPort(SerialPort&&) = delete;
   auto operator=(const SerialPort&) -> SerialPort& = delete;
   auto operator=(SerialPort &&) -> SerialPort& = delete;
   ~SerialPort();

   [[nodiscard]] static auto get(std::optional<uint16_t> rx_pin,
                                 std::optional<uint16_t> tx_pin,
                                 std::optional<std::string> device_name,
                                 std::optional<uint32_t> baud_rate) -> SerialPort&;

   [[nodiscard]] auto read() const -> std::string;
   void write(const std::string& message);

 private:
   explicit SerialPort(uint16_t rx_pin_number,
                       uint16_t tx_pin_number,
                       std::string device_name,
                       uint32_t baud_rate);

   BasePin& m_rx_pin;
   BasePin& m_tx_pin;
   std::string m_device_name{};
   uint32_t m_baud_rate{};
   int m_file_descriptor{};
};
} // namespace gpio::serial

#endif // ODROIDGPIO_SERIALPORT_HPP
