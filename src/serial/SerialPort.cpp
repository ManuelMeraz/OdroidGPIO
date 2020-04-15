#include "detail/serial/serial.hpp"

#include <iostream>
#include <odroid/gpio.hpp>
#include <odroid/serial/SerialPort.hpp>
#include <sstream>
#include <utility>

namespace {
struct SerialPortDeleter
{
   void operator()(gpio::serial::SerialPort* serial_port) const
   {
      delete serial_port;
   }
};

// globals
std::unique_ptr<gpio::serial::SerialPort, SerialPortDeleter> g_serial_port{nullptr};
} // namespace

gpio::serial::SerialPort::SerialPort(std::string device_name,
                                     uint32_t baud_rate,
                                     uint16_t rx_pin_number,
                                     uint16_t tx_pin_number) :
   m_rx_pin(gpio::get<BasePin>(rx_pin_number)),
   m_tx_pin(gpio::get<BasePin>(tx_pin_number)),
   m_device_name(std::move(device_name)),
   m_baud_rate(baud_rate),
   m_file_descriptor(gpio::serial::open(m_device_name, m_baud_rate))
{
   if (!gpio::setup()) {
      throw std::runtime_error("Failed to initialize gpio");
   }
}

gpio::serial::SerialPort::~SerialPort()
{
   gpio::serial::clear(m_file_descriptor);
   gpio::serial::close(m_file_descriptor);
}

auto gpio::serial::SerialPort::get(std::optional<std::string> device_name,
                                   std::optional<uint32_t> baud_rate,
                                   std::optional<uint16_t> rx_pin,
                                   std::optional<uint16_t> tx_pin) -> gpio::serial::SerialPort&
{
   if (g_serial_port == nullptr) {
      if (!device_name or !baud_rate) {
         if (!device_name) {
            std::cerr << "Missing device name from argument" << std::endl;
         }

         if (!baud_rate) {
            std::cerr << "Missing baud rate from argument" << std::endl;
         }

         throw std::invalid_argument("Need rx pin, tx pin, and device name to get serial port");
      }

      g_serial_port.reset(new gpio::serial::SerialPort(*device_name, *baud_rate, *rx_pin, *tx_pin));
   }

   return *g_serial_port;
}

auto gpio::serial::SerialPort::read() const -> std::string
{
   std::stringstream ss;
   while (gpio::serial::data_available(m_file_descriptor)) {
      ss << gpio::serial::read_char(m_file_descriptor);
   }

   return ss.str();
}

void gpio::serial::SerialPort::write(const std::string& message)
{
   gpio::serial::write(m_file_descriptor, message);
}
