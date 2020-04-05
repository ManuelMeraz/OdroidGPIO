#ifndef ODROIDGPIO_PINDATABASE_HPP
#define ODROIDGPIO_PINDATABASE_HPP

#include <memory>
#include <odroid/digital/DigitalPin.hpp>
#include <odroid/pwm/PWMPin.hpp>
#include <unordered_map>
#include <variant>

namespace gpio {
class PinDatabase
{
 public:
   PinDatabase(const PinDatabase&) = delete;
   PinDatabase(PinDatabase&&) = delete;
   auto operator=(const PinDatabase&) -> PinDatabase& = delete;
   auto operator=(PinDatabase &&) -> PinDatabase& = delete;
   ~PinDatabase() = default;

   static auto contains(uint8_t pin_number) -> bool;

   static auto emplace(std::pair<uint8_t, std::unique_ptr<BasePin>>&& data) -> void;
   //   template <
   //      typename Pin, typename... Args,
   //      typename std::enable_if_t<
   //         std::is_base_of_v<PinDatabase, std::decay_t<Pin>>, int> = 0>
   //   auto get(uint16_t pin_number, Args &&... args) -> Pin & {
   //      int const id = utils::get_new_id<Pin>();
   //      auto &storables = database::utils::retrieve_all<Pin>();
   //
   //      auto const comp = [](Pin const &lhs, int id) { return lhs.id() < id; };
   //
   //      // Find the position to insert in the cache
   //      auto pos = std::lower_bound(begin(storables), end(storables), id, comp);
   //
   //      // Store into local cache
   //      auto &storable = *storables.emplace(pos, id, std::forward<Args>(args)...);
   //
   //   // Insert into the database
   //   database::utils::insert(storable);
   //
   //   return storable;
   //}

 private:
   explicit PinDatabase() = default;
   std::unordered_map<uint8_t, std::unique_ptr<BasePin>> m_database;
};
} // namespace gpio

#endif // ODROIDGPIO_PINDATABASE_HPP
