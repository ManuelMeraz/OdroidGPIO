#ifndef ODROIDGPIO_BASEPIN_HPP
#define ODROIDGPIO_BASEPIN_HPP

#include <memory>

namespace gpio {
class BasePin
{
 public:
   using uPtr = std::unique_ptr<BasePin>;
   using sPtr = std::shared_ptr<BasePin>;

   BasePin() = delete;
   BasePin(const BasePin&) = delete;
   BasePin(BasePin&&) = delete;
   auto operator=(const BasePin&) -> BasePin& = delete;
   auto operator=(BasePin &&) -> BasePin& = delete;

 protected:
   explicit BasePin(uint8_t pin_number);
   ~BasePin() = default;

 private:
   uint8_t m_pin_number{};
};
} // namespace gpio

#endif // ODROIDGPIO_BASEPIN_HPP
