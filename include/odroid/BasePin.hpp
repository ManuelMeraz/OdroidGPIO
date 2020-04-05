#ifndef ODROIDGPIO_BASEPIN_HPP
#define ODROIDGPIO_BASEPIN_HPP

#include <cstdint>

namespace gpio {
class BasePin
{
 public:
   BasePin() = delete;
   BasePin(const BasePin&) = delete;
   BasePin(BasePin&&) = delete;
   auto operator=(const BasePin&) -> BasePin& = delete;
   auto operator=(BasePin &&) -> BasePin& = delete;
   ~BasePin() = default;

   [[nodiscard]] auto pin_number() const -> uint16_t;

 protected:
   explicit BasePin(uint16_t pin_number);

 private:
   friend class PinDatabase;
   uint16_t m_pin_number;
};
} // namespace gpio

#endif // ODROIDGPIO_BASEPIN_HPP
