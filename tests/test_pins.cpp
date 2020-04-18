#include <gtest/gtest.h>
#include <iostream>
#include <odroid/gpio.hpp>

namespace gpio {
namespace {
TEST(TestDigitalPin, GettersAndSetters)
{
   constexpr size_t NUM_PINS{5};
   constexpr std::array<uint8_t, NUM_PINS> PIN_NUMBERS{1, 2, 3, 4, 5};
   for (size_t pin_number = PIN_NUMBERS[0]; pin_number <= PIN_NUMBERS[4]; ++pin_number) {

      auto& digital_pin = gpio::get<digital::Pin>(pin_number, digital::Mode::OUTPUT);
      ASSERT_EQ(pin_number, digital_pin.pin_number())
         << "Pin number passed in to digital pin constructor must be equal to its pin number";
      ASSERT_EQ(digital::Mode::OUTPUT, digital_pin.mode())
         << "Digital mode passed in to digital pin constructor must be equal to its mode";

      digital_pin.mode(digital::Mode::INPUT);
      ASSERT_EQ(digital::Mode::INPUT, digital_pin.mode())
         << "Digital mode that was set must be equal to its mode";
   }
}

TEST(TestDigitalPin, TestSingleton)
{
   constexpr uint8_t PIN_NUMBER{10};
   auto& digital_pin = gpio::get<digital::Pin>(PIN_NUMBER, digital::Mode::INPUT);
   auto& second_pin_instance = gpio::get<digital::Pin>(PIN_NUMBER);
   ASSERT_EQ(&digital_pin, &second_pin_instance)
      << "Memory addresses must be the same for singleton";

   ASSERT_EQ(digital::Mode::INPUT, second_pin_instance.mode())
      << "The second instance of the digital pin must have the same mode as the originally constructed pin";

   digital_pin.mode(digital::Mode::OUTPUT);
   ASSERT_EQ(digital::Mode::OUTPUT, second_pin_instance.mode())
      << "When any instance of pin changes a value, all instances must also change.";

   try {
      gpio::get<pwm::Pin>(PIN_NUMBER, pwm::Mode::OUTPUT);
      FAIL()
         << "It must be impossible to get a pin that has already been constructed as another type.";
   } catch (const std::invalid_argument& e) {
      SUCCEED();
   }
}

} // namespace
} // namespace gpio

auto main(int argc, char** argv) -> int
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
   return 0;
}