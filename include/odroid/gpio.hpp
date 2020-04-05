#ifndef ODROID_GPIO_HPP
#define ODROID_GPIO_HPP

#include "odroid/digital/Pin.hpp"
#include "odroid/digital/digital.hpp"
#include "odroid/pwm/Pin.hpp"
#include "odroid/pwm/pwm.hpp"

#include <chrono>
#include <cstdint>

namespace gpio {
auto is_ready() -> bool;
void sleep(std::chrono::milliseconds duration);
} // namespace gpio

#endif // ODROID_GPIO_HPP
