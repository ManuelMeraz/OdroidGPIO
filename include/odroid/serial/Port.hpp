#ifndef ODROIDGPIO_PORT_HPP
#define ODROIDGPIO_PORT_HPP

#include <odroid/BasePin.hpp>

namespace gpio {
class Database;
} // namespace gpio

namespace gpio::serial {
class Port
{
   friend class gpio::Database;

 public:
   Port() = delete;
   Port(const Port&) = delete;
   Port(Port&&) = delete;
   auto operator=(const Port&) -> Port& = delete;
   auto operator=(Port &&) -> Port& = delete;

   [[nodiscard]] auto read() const -> std::string;
   void write(const std::string& message);

 private:
   explicit Port(std::string device_name,
                 uint32_t baud_rate,
                 uint16_t rx_pin_number = 0,
                 uint16_t tx_pin_number = 0);
   ~Port();

   BasePin& m_rx_pin;
   BasePin& m_tx_pin;
   std::string m_device_name{};
   uint32_t m_baud_rate{};
   int m_file_descriptor{};
};
} // namespace gpio::serial

#endif // ODROIDGPIO_PORT_HPP
