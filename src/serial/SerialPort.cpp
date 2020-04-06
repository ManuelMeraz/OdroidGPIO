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

gpio::serial::SerialPort::SerialPort(uint16_t rx_pin_number,
                                     uint16_t tx_pin_number,
                                     std::string device_name,
                                     uint32_t baud_rate) :
   m_rx_pin(gpio::get<BasePin>(rx_pin_number)),
   m_tx_pin(gpio::get<BasePin>(tx_pin_number)),
   m_device_name(std::move(device_name)),
   m_baud_rate(baud_rate),
   m_file_descriptor(gpio::serial::open(m_device_name, m_baud_rate))
{}

gpio::serial::SerialPort::~SerialPort()
{
   gpio::serial::clear(m_file_descriptor);
   gpio::serial::close(m_file_descriptor);
}

auto gpio::serial::SerialPort::get(std::optional<uint16_t> rx_pin,
                                   std::optional<uint16_t> tx_pin,
                                   std::optional<std::string> device_name,
                                   std::optional<uint32_t> baud_rate) -> gpio::serial::SerialPort&
{
   if (g_serial_port == nullptr) {
      if (!rx_pin || !tx_pin || !device_name || !baud_rate) {
         if (!rx_pin) {
            std::cerr << "Missing rx pin from argument" << std::endl;
         }

         if (!tx_pin) {
            std::cerr << "Missing tx pin from argument" << std::endl;
         }

         if (!device_name) {
            std::cerr << "Missing device name from argument" << std::endl;
         }

         if (!baud_rate) {
            std::cerr << "Missing baud rate from argument" << std::endl;
         }

         throw std::invalid_argument("Need rx pin, tx pin, and device name to get serial port");
      }

      g_serial_port.reset(new gpio::serial::SerialPort(*rx_pin, *tx_pin, *device_name, *baud_rate));
   }

   return *g_serial_port;
}

auto gpio::serial::SerialPort::read() const -> std::string
{
   std::stringstream ss;
   while (gpio::serial::data_available(m_file_descriptor)) {
      ss << gpio::serial::read_byte(m_file_descriptor);
   }

   return ss.str();
}

void gpio::serial::SerialPort::write(const std::string& message)
{
   gpio::serial::write(m_file_descriptor, message);
}