#ifndef ODROIDGPIO_SERIALPORT_HPP
#define ODROIDGPIO_SERIALPORT_HPP

#include <odroid/BasePin.hpp>

namespace gpio {
class Database;
} // namespace gpio

namespace gpio::serial {
class SerialPort
{
   friend class gpio::Database;

 public:
   SerialPort() = delete;
   SerialPort(const SerialPort&) = delete;
   SerialPort(SerialPort&&) = delete;
   auto operator=(const SerialPort&) -> SerialPort& = delete;
   auto operator=(SerialPort &&) -> SerialPort& = delete;

   [[nodiscard]] auto read() const -> std::string;
   void write(const std::string& message);

 private:
   explicit SerialPort(std::string device_name,
                       uint32_t baud_rate,
                       uint16_t rx_pin_number = 0,
                       uint16_t tx_pin_number = 0);
   ~SerialPort();

   BasePin& m_rx_pin;
   BasePin& m_tx_pin;
   std::string m_device_name{};
   uint32_t m_baud_rate{};
   int m_file_descriptor{};
};
} // namespace gpio::serial

#endif // ODROIDGPIO_SERIALPORT_HPP
