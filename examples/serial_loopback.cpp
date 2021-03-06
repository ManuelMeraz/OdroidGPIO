#include <iostream>
#include <odroid/gpio.hpp>

/**
 *  Needs to be enabled. Disabled by default.
 * https://wiki.odroid.com/odroid-n2/application_note/gpio/uart
 */
constexpr auto DEVICE_NAME{"/dev/ttyS1"};
constexpr uint32_t BAUD_RATE{115200};

namespace serial = gpio::serial;
using namespace std::chrono_literals;
auto main() -> int
{
   auto& serial_port = gpio::get<serial::Port>(DEVICE_NAME, BAUD_RATE);

   serial_port.write("This is the serial loopback mesage!");
   gpio::sleep(10ms);
   std::cout << serial_port.read() << std::endl;
   return 0;
}
