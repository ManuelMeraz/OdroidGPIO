#include "gtest/gtest.h"
#include <chrono>
#include <odroid/gpio.hpp>

namespace gpio {
namespace {
constexpr size_t NUM_REPEATED_TESTS = 10;

// Tests that the Foo::Bar() method does Abc.
TEST(TestPublicGPIO, SetupAlwaysTrue)
{
   // Make sure setting up multiple times doesn't crash
   for (size_t i = 0; i < NUM_REPEATED_TESTS; ++i) {
      ASSERT_TRUE(gpio::setup()) << "gpio::setup() must always be true";
   }
}

TEST(TestPublicGPIO, sleepIsAccurate)
{
   using namespace std::chrono_literals;
   for (size_t i = 0; i < NUM_REPEATED_TESTS; ++i) {
      const auto start = std::chrono::high_resolution_clock::now();
      gpio::sleep(25ms);
      const auto elapsed = std::chrono::high_resolution_clock::now() - start;
      ASSERT_TRUE(elapsed >= 25ms) << "gpio::sleep(duration) must be accurate";
   }
}

TEST(TestPublicGPIO, getFromDatabase)
{
   auto& base_pin = gpio::get<BasePin>(0);
   ASSERT_EQ(base_pin.pin_number(), 0);

   try {
      auto& pwm_pin = gpio::get<gpio::pwm::PWMPin>(0, pwm::Mode::OFF);
      (void)pwm_pin;
      FAIL() << "A pin was generated despite another pin existing with the same number.";
   } catch (const std::invalid_argument& e) {
      SUCCEED();
   }

   auto& good_pwm_pin = gpio::get<gpio::pwm::PWMPin>(1, pwm::Mode::OFF);
   ASSERT_EQ(good_pwm_pin.pin_number(), 1);

   auto& digital_pin = gpio::get<gpio::digital::DigitalPin>(2, digital::Mode::OFF);
   ASSERT_EQ(digital_pin.pin_number(), 2);

   constexpr uint32_t BAUD_RATE = 115200;
   try {
      auto& serial_port = gpio::get<serial::SerialPort>("/dev/tty0", BAUD_RATE);
      (void)serial_port;
      SUCCEED();
   } catch (const std::runtime_error& e) {
      FAIL() << e.what();
   }

   constexpr uint16_t BOGUS_DEVICE_NUM = 5;
   auto& i2c_device = gpio::get<I2C::I2CDevice>(BOGUS_DEVICE_NUM);
   (void)i2c_device;
}
} // namespace
} // namespace gpio

auto main(int argc, char** argv) -> int
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}