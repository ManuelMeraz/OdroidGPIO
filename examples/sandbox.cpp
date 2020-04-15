#include <chrono>
#include <cstring>
#include <iostream>
#include <odroid/gpio.hpp>
#include <thread>

/* These enums are straight out of the adafruit_bno055 header file */
enum adafruit_bno055_reg_t {
   /* Page id register definition */
   BNO055_PAGE_ID_ADDR = 0X07,

   /* PAGE0 REGISTER DEFINITION START*/
   BNO055_CHIP_ID_ADDR = 0x00,

   /* Linear acceleration data registers */
   BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR = 0X28,

   /* Mode registers */
   BNO055_OPR_MODE_ADDR = 0X3D,
   BNO055_PWR_MODE_ADDR = 0X3E,

   BNO055_SYS_TRIGGER_ADDR = 0X3F,
};

/** BNO055 power settings */
enum adafruit_bno055_powermode_t {
   POWER_MODE_NORMAL = 0X00,
};

/** Operation mode settings **/
enum adafruit_bno055_opmode_t { OPERATION_MODE_CONFIG = 0X00, OPERATION_MODE_NDOF = 0X0C };

/** Vector Mappings **/
enum adafruit_vector_type_t {
   VECTOR_LINEARACCEL = BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR,
};

// device ID for odroid n2
constexpr uint32_t DEVICE_ID = 0x28;

constexpr uint32_t BNO055_ID = 0xA0;

using namespace std::chrono_literals;

int main()
{
   auto& device = gpio::I2C::I2CDevice::get(DEVICE_ID);
   std::cout << "I2C communication successfully setup.\n";

   uint8_t id = device.read_8_bits(BNO055_CHIP_ID_ADDR);
   if (id != BNO055_ID) {
      gpio::sleep(1s); // hold on for boot
      id = device.read_8_bits(BNO055_CHIP_ID_ADDR);
      if (id != BNO055_ID) {
         std::cerr << "Couldn't verify that this was the right device" << std::endl;
         std::cerr << "Valid id: " << BNO055_ID << " got id: " << static_cast<uint32_t>(id)
                   << std::endl;
         return 1;
      }
   }

   // Switch device to measurement mode
   device.write_8_bits(BNO055_OPR_MODE_ADDR, OPERATION_MODE_CONFIG);
   /* Make sure we have the right device */

   /* Reset */
   device.write_8_bits(BNO055_SYS_TRIGGER_ADDR, 0x20);
   /* Delay incrased to 30ms due to power issues https://tinyurl.com/y375z699 */
   gpio::sleep(30ms);

   while (device.read_8_bits(BNO055_CHIP_ID_ADDR) != BNO055_ID) {
      gpio::sleep(10ms);
   }

   gpio::sleep(50ms);

   /* Set to normal power mode */
   device.write_8_bits(BNO055_PWR_MODE_ADDR, POWER_MODE_NORMAL);
   gpio::sleep(10ms);

   device.write_8_bits(BNO055_PAGE_ID_ADDR, 0);

   device.write_8_bits(BNO055_SYS_TRIGGER_ADDR, 0x0);
   gpio::sleep(10ms);
   /* Set the requested operating mode (see section 3.3) */
   device.write_8_bits(BNO055_OPR_MODE_ADDR, OPERATION_MODE_NDOF);
   gpio::sleep(20ms);

   struct Vector3
   {
      int16_t x;
      int16_t y;
      int16_t z;
   } acceleration{0, 0, 0};

   constexpr size_t BUFFER_SIZE = 6;
   while (true) {
      auto data = device.read<BUFFER_SIZE>(VECTOR_LINEARACCEL);
      acceleration = *reinterpret_cast<Vector3*>(&data[0]);
      //      acceleration.x = static_cast<uint16_t>(data[0]) | static_cast<uint16_t>(data[1] <<
      //      8u); acceleration.y = static_cast<uint16_t>(data[2]) | static_cast<uint16_t>(data[3]
      //      << 8u); acceleration.z = static_cast<uint16_t>(data[4]) |
      //      static_cast<uint16_t>(data[5] << 8u);
      std::cout << "x: " << acceleration.x << ", y: " << acceleration.y << ", z: " << acceleration.z
                << "\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
   }
   return 0;
}