#include <iostream>
#include <odroid/gpio.hpp>
#include <wiringPi.h>
#include <wiringSerial.h>

auto main() -> int
{
   if (!gpio::setup()) {
      return 1;
   }

   namespace serial = gpio::serial;

   constexpr uint8_t RX_PIN = 10;
   constexpr uint8_t TX_PIN = 8;
   constexpr auto DEVICE_NAME = "/dev/ttyS1";
   constexpr uint32_t BAUD_RATE = 115200;
   auto& serial_port = serial::SerialPort::get(RX_PIN, TX_PIN, DEVICE_NAME, BAUD_RATE);

   serial_port.write("hello");
   std::cout << serial_port.read() << std::endl;
   return 0;
}
