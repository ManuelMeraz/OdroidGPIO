#include "detail/serial/serial.hpp"

#include <iostream>
#include <odroid/gpio.hpp>
#include <odroid/serial/SerialPort.hpp>
#include <sstream>
#include <utility>

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
