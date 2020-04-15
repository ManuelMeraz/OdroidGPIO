#include <iostream>
#include <odroid/gpio.hpp>

/**
 *  Needs to be enabled. Disabled by default.
 * https://wiki.odroid.com/odroid-n2/application_note/gpio/uart
 */
constexpr auto DEVICE_NAME{"/dev/ttyS1"};
constexpr uint32_t BAUD_RATE{115200};

namespace serial = gpio::serial;
auto main() -> int
{
   if (!gpio::setup()) {
      return 1;
   }

   auto& serial_port = serial::SerialPort::get(DEVICE_NAME, BAUD_RATE);

   serial_port.write("This is the serial loopback mesage!");
   gpio::sleep(std::chrono::milliseconds(10));
   std::cout << serial_port.read() << std::endl;
   return 0;
}
