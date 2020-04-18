#ifndef ODROIDGPIO_HPP
#define ODROIDGPIO_HPP

#include "BasePin.hpp"
#include "Database.hpp"
#include "odroid/I2C/I2CDevice.hpp"
#include "odroid/digital/Pin.hpp"
#include "odroid/digital/digital.hpp"
#include "odroid/pwm/Pin.hpp"
#include "odroid/pwm/pwm.hpp"
#include "odroid/serial/SerialPort.hpp"

#include <chrono>
#include <cstdint>

namespace gpio {
auto setup() -> bool;
void sleep(std::chrono::milliseconds duration);

template <typename Pin,
          typename... Args,
          typename std::enable_if_t<std::is_base_of_v<BasePin, std::decay_t<Pin>>, int> = 0>
auto get(uint16_t pin_number, Args&&... args) -> Pin&
{
   return Database::get<Pin>(pin_number, args...);
}

template <typename I2CDevice,
          typename... Args,
          typename std::enable_if_t<std::is_same_v<gpio::I2C::I2CDevice, std::decay_t<I2CDevice>>,
                                    int> = 0>
static auto get(uint16_t device_number, Args&&... args) -> I2CDevice&
{
   return Database::get<I2CDevice>(device_number, args...);
}

template <
   typename SerialPort,
   typename... Args,
   typename std::enable_if_t<std::is_same_v<gpio::serial::SerialPort, std::decay_t<SerialPort>>,
                             int> = 0>
static auto get(const std::string& device_name, Args&&... args) -> SerialPort&
{
   return Database::get<SerialPort>(device_name, args...);
}
} // namespace gpio

#endif // ODROIDGPIO_HPP
