#include <iostream>
#include <odroid/gpio.hpp>

constexpr uint8_t RX_PIN{10};
constexpr uint8_t TX_PIN{8};
constexpr auto DEVICE_NAME{"/dev/ttyS1"};
constexpr uint32_t BAUD_RATE{115200};

namespace serial = gpio::serial;

auto main() -> int
{
   if (!gpio::setup()) {
      return 1;
   }

   auto& serial_port = serial::SerialPort::get(RX_PIN, TX_PIN, DEVICE_NAME, BAUD_RATE);

   serial_port.write("This is the serial loopback mesage!");
   gpio::sleep(std::chrono::milliseconds(10));
   std::cout << serial_port.read() << std::endl;
   return 0;
}
