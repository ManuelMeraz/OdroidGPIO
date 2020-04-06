#include <iostream>
#include <odroid/gpio.hpp>
#include <odroid/serial/SerialPort.hpp>
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
                                     std::string device_name) :
   m_rx_pin(gpio::get<BasePin>(rx_pin_number)),
   m_tx_pin(gpio::get<BasePin>(tx_pin_number)),
   m_device_name(std::move(device_name))
{
   // initial serial port here
}
gpio::serial::SerialPort::~SerialPort() {}

auto gpio::serial::SerialPort::get(std::optional<uint16_t> rx_pin,
                                   std::optional<uint16_t> tx_pin,
                                   std::optional<std::string> device_name)
   -> gpio::serial::SerialPort&
{
   if (g_serial_port == nullptr) {
      if (!rx_pin || !tx_pin || !device_name) {
         if (!rx_pin) {
            std::cerr << "Missing rx pin from argument" << std::endl;
         }

         if (!tx_pin) {
            std::cerr << "Missing tx pin from argument" << std::endl;
         }

         if (!device_name) {
            std::cerr << "Missing device name pin from argument" << std::endl;
         }

         std::__throw_invalid_argument("Need rx pin, tx pin, and device name to get serial port");
      }

      g_serial_port.reset(new gpio::serial::SerialPort(*rx_pin, *tx_pin, *device_name));
   }

   return *g_serial_port;
}

auto gpio::serial::SerialPort::read() const -> std::string
{
   return std::__cxx11::string();
}

void gpio::serial::SerialPort::write(const std::string& message) {}
