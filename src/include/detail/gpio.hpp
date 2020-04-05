#ifndef DETAIL_ODROIDGPIO_GPIO_HPP
#define DETAIL_ODROIDGPIO_GPIO_HPP

#include <cstdint>
namespace gpio {
void pin_mode(uint16_t pin_number, uint16_t mode);
} // namespace gpio

#endif // DETAIL_ODROIDGPIO_GPIO_HPP
