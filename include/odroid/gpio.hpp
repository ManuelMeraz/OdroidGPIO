#ifndef ODROIDGPIO_HPP
#define ODROIDGPIO_HPP

#include "odroid/digital/DigitalPin.hpp"
#include "odroid/digital/digital.hpp"
#include "odroid/pwm/PWMPin.hpp"
#include "odroid/pwm/pwm.hpp"

#include <chrono>
#include <cstdint>

namespace gpio {
auto is_ready() -> bool;
void sleep(std::chrono::milliseconds duration);

// template <
//   typename Pin, typename... Args,
//   typename std::enable_if_t<
//      std::is_base_of_v<PinDatabase, std::decay_t<Pin>>, int> = 0>
// auto get(uint16_t pin_number, Args &&... args) -> Pin & {
//   int const id = utils::get_new_id<Pin>();
//   auto &storables = database::utils::retrieve_all<Pin>();
//
//   auto const comp = [](Pin const &lhs, int id) { return lhs.id() < id; };
//
//   // Find the position to insert in the cache
//   auto pos = std::lower_bound(begin(storables), end(storables), id, comp);
//
//   // Store into local cache
//   auto &storable = *storables.emplace(pos, id, std::forward<Args>(args)...);
//
//   // Insert into the database
//   database::utils::insert(storable);
//
//   return storable;
//}
} // namespace gpio

#endif // ODROIDGPIO_HPP
