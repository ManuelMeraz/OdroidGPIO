#ifndef ODROIDGPIO_HPP
#define ODROIDGPIO_HPP

#include "BasePin.hpp"
#include "PinDatabase.hpp"
#include "odroid/digital/DigitalPin.hpp"
#include "odroid/digital/digital.hpp"
#include "odroid/pwm/PWMPin.hpp"
#include "odroid/pwm/pwm.hpp"

#include <chrono>
#include <cstdint>

namespace gpio {
auto is_ready() -> bool;
void sleep(std::chrono::milliseconds duration);

template <typename Pin,
          typename... Args,
          typename std::enable_if_t<std::is_base_of_v<BasePin, std::decay_t<Pin>>, int> = 0>
auto get(uint8_t pin_number, Args&&... args) -> Pin&
{
   return PinDatabase::get<Pin>(pin_number, args...);
}
} // namespace gpio

#endif // ODROIDGPIO_HPP
