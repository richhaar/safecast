/*****************************************************************************
 * @file safe_cast.hpp
 * @brief Provides safe casting utilities to prevent overflow and underflow.
 * @author Richard Haar https://github.com/richhaar
 * @date 28/02/2025
 *
 * @licenseblock{MIT License}
 * Copyright (c) 2025 Richard Haar
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * @endlicenseblock
 ****************************************************************************/
#ifndef _SAFE_CAST_HPP_
#define _SAFE_CAST_HPP_

#include <concepts>
#include <format>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace sc {

/**
 * @brief Concept to check two types are both signed integers.
 */
template <typename T, typename U>
concept signed_integers = std::signed_integral<T> && std::signed_integral<U>;

/**
 * @brief Concept to check two types are both unsigned integers.
 */
template <typename T, typename U>
concept unsigned_integers =
    std::unsigned_integral<T> && std::unsigned_integral<U>;

/**
 * @brief Throws an overflow error with a formatted message.
 * @tparam From The source type of the cast.
 * @tparam To The destination type of the cast.
 * @param value The value that caused the overflow.
 * @throws std::overflow_error
 */
template <std::integral To, std::integral From>
constexpr void throw_overflow(From value) {
  throw std::overflow_error(
      std::format("Overflow casting from {} (value: {}) to {}.",
                  typeid(From).name(), value, typeid(To).name()));
}

/**
 * @brief Throws an underflow error with a formatted message.
 * @tparam From The source type of the cast.
 * @tparam To The destination type of the cast.
 * @param value The value that caused the underflow.
 * @throws std::underflow_error
 */
template <std::integral To, std::integral From>
constexpr void throw_underflow(From value) {
  throw std::underflow_error(
      std::format("Underflow casting from {} (value: {}) to {}.",
                  typeid(From).name(), value, typeid(To).name()));
}

/**
 * @brief Performs a safe cast between integer types, checking for overflow and
 * underflow.
 * @tparam To The destination type of the cast.
 * @tparam From The source type of the cast.
 * @param value The value to be cast.
 * @return The safely cast value.
 * @throws std::overflow_error if the cast would result in overflow.
 * @throws std::underflow_error if the cast would result in underflow.
 */
template <std::integral To, std::integral From>
To safe_cast(From value) noexcept(false) {
  if constexpr (signed_integers<To, From> || unsigned_integers<To, From>) {
    if (value > std::numeric_limits<To>::max()) {
      throw_overflow<To, From>(value);
    }
    if (value < std::numeric_limits<To>::min()) {
      throw_underflow<To, From>(value);
    }
  } else if constexpr (std::unsigned_integral<From> &&
                       std::signed_integral<To>) {
    if (value >
        static_cast<std::make_unsigned_t<To>>(std::numeric_limits<To>::max())) {
      throw_overflow<To, From>(value);
    }
  } else if constexpr (std::signed_integral<From> &&
                       std::unsigned_integral<To>) {
    if (value < 0) {
      throw_underflow<To, From>(value);
    }
    if constexpr (sizeof(From) > sizeof(To)) {
      if (value > static_cast<From>(std::numeric_limits<To>::max())) {
        throw_overflow<To, From>(value);
      }
    }
  }
  return static_cast<To>(value);
}
}  // namespace sc
#endif
