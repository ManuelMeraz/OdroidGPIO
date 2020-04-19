#ifndef ODROIDGPIO_DATABASE_HPP
#define ODROIDGPIO_DATABASE_HPP

#include <nameof/nameof.hpp>
#include <odroid/BasePin.hpp>
#include <odroid/I2C/Bus.hpp>
#include <odroid/serial/Port.hpp>
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

   template <typename Bus,
             typename... Args,
             typename std::enable_if_t<std::is_same_v<gpio::I2C::Bus, std::decay_t<Bus>>, int> = 0>
   static auto get(uint8_t device_number, Args&&... args) -> Bus&
   {
      auto& database = Database::instance();
      auto& stored_buses = database.stored_I2C_buses();
      auto find_bus = stored_buses.find(device_number);
      if (find_bus != stored_buses.end()) {
         auto& bus = *find_bus->second;
         return static_cast<Bus&>(bus);
      }

      return database.make<Bus>(device_number, args...);
   }

   template <
      typename SerialPort,
      typename... Args,
             typename std::enable_if_t<std::is_same_v<gpio::serial::Port, std::decay_t<SerialPort>>,
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
   auto stored_I2C_buses() -> std::unordered_map<uint16_t, gpio::I2C::Bus*>&;
   auto stored_serial_ports() -> std::unordered_map<std::string, gpio::serial::Port*>&;

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

   template <typename Bus,
             typename... Args,
             typename std::enable_if_t<std::is_same_v<gpio::I2C::Bus, std::decay_t<Bus>>, int> = 0>
   static auto make(uint16_t device_number, Args&&... args) -> Bus&
   {
      auto& stored_buses = instance().stored_I2C_buses();
      auto* bus = new Bus(device_number, args...);
      stored_buses.emplace(std::make_pair(device_number, std::move(bus)));
      return *bus;
   }

   template <
      typename SerialPort,
      typename... Args,
             typename std::enable_if_t<std::is_same_v<gpio::serial::Port, std::decay_t<SerialPort>>,
                                       int> = 0>
   static auto make(const std::string& device_name, Args&&... args) -> SerialPort&
   {
      auto& stored_ports = instance().stored_serial_ports();
      auto* port = new SerialPort(device_name, args...);
      stored_ports.emplace(std::make_pair(device_name, std::move(port)));
      return *port;
   }

   std::unordered_map<uint16_t, BasePin*> m_stored_pins{};
   std::unordered_map<uint16_t, gpio::I2C::Bus*> m_stored_I2C_buses{};
   std::unordered_map<std::string, gpio::serial::Port*> m_stored_serial_ports{};
};
} // namespace gpio

#endif // ODROIDGPIO_DATABASE_HPP
