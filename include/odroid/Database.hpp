#ifndef ODROIDGPIO_DATABASE_HPP
#define ODROIDGPIO_DATABASE_HPP

#include <nameof/nameof.hpp>
#include <odroid/BasePin.hpp>
#include <odroid/I2C/I2CDevice.hpp>
#include <odroid/serial/SerialPort.hpp>
#include <unordered_map>

namespace gpio {
class Database
{
 public:
   Database(const Database&) = delete;
   Database(Database&&) = delete;
   auto operator=(const Database&) -> Database& = delete;
   auto operator=(Database &&) -> Database& = delete;

   template <typename Pin,
             typename... Args,
             typename std::enable_if_t<std::is_base_of_v<BasePin, std::decay_t<Pin>>, int> = 0>
   static auto get(uint16_t pin_number, Args&&... args) -> Pin&
   {
      auto& database = Database::instance();
      auto& stored_pins = database.stored_pins();
      auto find_pin = stored_pins.find(pin_number);
      if (find_pin != stored_pins.end()) {
         auto& pin = *find_pin->second;
         if (nameof::nameof_type<std::decay_t<Pin>>() != pin.type()) {
            throw std::invalid_argument("Attempted to get pin that exists with incorrect type");
         }

         return static_cast<Pin&>(pin);
      }

      return database.make<Pin>(pin_number, args...);
   }

   template <typename I2CDevice,
             typename... Args,
             typename std::
                enable_if_t<std::is_same_v<gpio::I2C::I2CDevice, std::decay_t<I2CDevice>>, int> = 0>
   static auto get(uint8_t device_number, Args&&... args) -> I2CDevice&
   {
      auto& database = Database::instance();
      auto& stored_devices = database.stored_I2C_devices();
      auto find_device = stored_devices.find(device_number);
      if (find_device != stored_devices.end()) {
         auto& device = *find_device->second;
         return static_cast<I2CDevice&>(device);
      }

      return database.make<I2CDevice>(device_number, args...);
   }

   template <
      typename SerialPort,
      typename... Args,
      typename std::enable_if_t<std::is_same_v<gpio::serial::SerialPort, std::decay_t<SerialPort>>,
                                int> = 0>
   static auto get(const std::string& device_name, Args&&... args) -> SerialPort&
   {
      auto& database = Database::instance();
      auto& stored_ports = database.stored_serial_ports();
      auto find_port = stored_ports.find(device_name);
      if (find_port != stored_ports.end()) {
         auto& port = *find_port->second;
         return static_cast<SerialPort&>(port);
      }

      return database.make<SerialPort>(device_name, args...);
   }

 private:
   explicit Database() = default;
   ~Database();

   static auto instance() -> Database&;
   auto stored_pins() -> std::unordered_map<uint16_t, BasePin*>&;
   auto stored_I2C_devices() -> std::unordered_map<uint16_t, gpio::I2C::I2CDevice*>&;
   auto stored_serial_ports() -> std::unordered_map<std::string, gpio::serial::SerialPort*>&;

   template <typename Pin,
             typename... Args,
             typename std::enable_if_t<std::is_base_of_v<BasePin, std::decay_t<Pin>>, int> = 0>
   static auto make(uint16_t pin_number, Args&&... args) -> Pin&
   {
      auto& stored_pins = instance().stored_pins();
      auto* pin = new Pin(pin_number, args...);
      pin->type(nameof::nameof_type<std::decay_t<Pin>>());
      stored_pins.emplace(std::make_pair(pin_number, std::move(pin)));
      return *pin;
   }

   template <typename I2CDevice,
             typename... Args,
             typename std::
                enable_if_t<std::is_same_v<gpio::I2C::I2CDevice, std::decay_t<I2CDevice>>, int> = 0>
   static auto make(uint16_t device_number, Args&&... args) -> I2CDevice&
   {
      auto& stored_devices = instance().stored_I2C_devices();
      auto* device = new I2CDevice(device_number, args...);
      stored_devices.emplace(std::make_pair(device_number, std::move(device)));
      return *device;
   }

   template <
      typename SerialPort,
      typename... Args,
      typename std::enable_if_t<std::is_same_v<gpio::serial::SerialPort, std::decay_t<SerialPort>>,
                                int> = 0>
   static auto make(const std::string& device_name, Args&&... args) -> SerialPort&
   {
      auto& stored_ports = instance().stored_serial_ports();
      auto* port = new SerialPort(device_name, args...);
      stored_ports.emplace(std::make_pair(device_name, std::move(port)));
      return *port;
   }

   std::unordered_map<uint16_t, BasePin*> m_stored_pins{};
   std::unordered_map<uint16_t, gpio::I2C::I2CDevice*> m_stored_I2C_devices{};
   std::unordered_map<std::string, gpio::serial::SerialPort*> m_stored_serial_ports{};
};
} // namespace gpio

#endif // ODROIDGPIO_DATABASE_HPP
