#include <iostream>
#include <odroid/gpio.hpp>

/* Make sure to set your I2C device to 100 khz for bno055 compatibility */

/* These enums are straight out of the adafruit_bno055 header file */
enum adafruit_bno055_reg_t {
   /* Page id register definition */
   BNO055_PAGE_ID_ADDR = 0X07,

   /* PAGE0 REGISTER DEFINITION START*/
   BNO055_CHIP_ID_ADDR = 0x00,

   /* Linear acceleration data registers */
   BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR = 0X28,

   /* Unit selection register */
   BNO055_UNIT_SEL_ADDR = 0x3B,

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

/**
 * Device ID for odroid n2 SDA.2 and SCL.2.
 * Physical pins 3 and 5 respectively on Odroid N2
 *
 * Use i2c utils to acquire hex value for this
 * i2cdetect -y 2
 */
constexpr uint32_t DEVICE_ID = 0x28;

/* Start address for bno055 */
constexpr uint32_t BNO055_ID = 0xA0;

using namespace std::chrono_literals;

namespace I2C = gpio::I2C;
auto main() -> int
{
   /* May optionally pass in sda and scl pin number to reserve them for code safety */
   auto& device = gpio::get<I2C::I2CDevice>(DEVICE_ID);
   std::cout << "I2C communication successfully setup.\n";

   /* Make sure we have the right device */
   uint8_t id = device.read_8_bits(BNO055_CHIP_ID_ADDR);
   if (id != BNO055_ID) {
      std::cerr << "Couldn't verify that this was the right device" << std::endl;
      std::cerr << "Valid id: " << BNO055_ID << " got id: " << static_cast<uint32_t>(id)
                << std::endl;
      return 1;
   }

   /* Switch device to measurement mode */
   device.write_8_bits(BNO055_OPR_MODE_ADDR, OPERATION_MODE_CONFIG);

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

   device.write_8_bits(BNO055_PAGE_ID_ADDR, 0x0);

   /* Set the output units */
   uint8_t unitsel = (0 << 7) | // Orientation = Android
                     (0 << 4) | // Temperature = Celsius
                     (0 << 2) | // Euler = Degrees
                     (1 << 1) | // Gyro = Rads
                     (0 << 0);  // Accelerometer = m/s^2
   device.write_8_bits(BNO055_UNIT_SEL_ADDR, unitsel);

   device.write_8_bits(BNO055_SYS_TRIGGER_ADDR, 0x0);
   gpio::sleep(10ms);

   /* Nine degrees of freedom mode */
   device.write_8_bits(BNO055_OPR_MODE_ADDR, OPERATION_MODE_NDOF);
   gpio::sleep(20ms);

   struct Vector3
   {
      int16_t x{};
      int16_t y{};
      int16_t z{};
   };

   Vector3 acceleration{};

   constexpr size_t VECTOR_SIZE = sizeof(Vector3); // 6 bytes
   while (true) {
      /* Array of byte data of size 6 */
      auto linear_acceleration_data = device.read<VECTOR_SIZE>(VECTOR_LINEARACCEL);

      /* Map data onto the vector */
      acceleration = *reinterpret_cast<Vector3*>(&linear_acceleration_data[0]);

      std::cout << "x: " << acceleration.x << ", y: " << acceleration.y << ", z: " << acceleration.z
                << std::endl;
      gpio::sleep(100ms);
   }

   return 0;
}
