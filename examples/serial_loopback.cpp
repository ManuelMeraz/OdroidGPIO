#include <iostream>
#include <odroid/gpio.hpp>

// These pins actually aren't needed to do serial communication, but for code safety
// It prevents these pins from being enabled by accident
constexpr uint8_t RX_PIN{16}; // physical pin 10 on odroid n2
constexpr uint8_t TX_PIN{15}; // physical pin 8 on odroid n2

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

   auto& serial_port = serial::SerialPort::get(DEVICE_NAME, BAUD_RATE, RX_PIN, TX_PIN);

   serial_port.write("This is the serial loopback mesage!");
   gpio::sleep(std::chrono::milliseconds(10));
   std::cout << serial_port.read() << std::endl;
   return 0;
}
