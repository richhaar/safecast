#ifndef _SAFE_CAST_HPP_
#define _SAFE_CAST_HPP_

#include <concepts>
#include <format>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace sc {
template <typename T, typename U>
concept signed_integers = std::signed_integral<T> && std::signed_integral<U>;

template <typename T, typename U>
concept unsigned_integers =
    std::unsigned_integral<T> && std::unsigned_integral<U>;

template <std::integral To, std::integral From>
To safe_cast(From value) {
  if constexpr (signed_integers<To, From> || unsigned_integers<To, From>) {
    if (value > std::numeric_limits<To>::max()) {
      throw std::overflow_error(
          std::format("Overflow casting from {} (value: {}) to {}.",
                      typeid(From).name(), value, typeid(To).name()));
    }
    if (value < std::numeric_limits<To>::min()) {
      throw std::underflow_error(
          std::format("Underflow casting from {} (value: {}) to {}.",
                      typeid(From).name(), value, typeid(To).name()));
    }
  } else if constexpr (std::unsigned_integral<From> &&
                       std::signed_integral<To>) {
    if (value >
        static_cast<std::make_unsigned_t<To>>(std::numeric_limits<To>::max())) {
      throw std::overflow_error(
          std::format("Overflow casting from {} (value: {}) to {}.",
                      typeid(From).name(), value, typeid(To).name()));
    }
  } else {  // std::unsigned_integral<From> -> std::unsigned_integral<To>
    if (value < 0) {
      throw std::underflow_error(
          std::format("Underflow casting from {} (value: {}) to {}.",
                      typeid(From).name(), value, typeid(To).name()));
    }
    if constexpr (sizeof(From) > sizeof(To)) {
      if (value > static_cast<From>(std::numeric_limits<To>::max())) {
        throw std::overflow_error(
            std::format("Overflow casting from {} (value: {}) to {}.",
                        typeid(From).name(), value, typeid(To).name()));
      }
    }
  }
  return static_cast<To>(value);
}

}  // namespace sc

#endif
