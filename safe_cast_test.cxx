/*****************************************************************************
 * @file safe_cast_test.cxx
 * @brief Provides testing for the safe_cast function.
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
#include "safe_cast.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

namespace sc {
namespace {

TEST(SafeCast, SignedUnderflow) {
  EXPECT_THROW(safe_cast<int8_t>(std::numeric_limits<int16_t>::min()),
               std::underflow_error);
  EXPECT_THROW(safe_cast<int16_t>(std::numeric_limits<int32_t>::min()),
               std::underflow_error);
  EXPECT_THROW(safe_cast<int32_t>(std::numeric_limits<int64_t>::min()),
               std::underflow_error);
}

TEST(SafeCast, UnsignedUnderflow) {
  EXPECT_THROW(safe_cast<uint8_t>(std::numeric_limits<int8_t>::min()),
               std::underflow_error);
  EXPECT_THROW(safe_cast<uint16_t>(std::numeric_limits<int8_t>::min()),
               std::underflow_error);
  EXPECT_THROW(safe_cast<uint32_t>(std::numeric_limits<int8_t>::min()),
               std::underflow_error);
  EXPECT_THROW(safe_cast<uint64_t>(std::numeric_limits<int8_t>::min()),
               std::underflow_error);
}

TEST(SafeCast, WidthOverflow) {
  EXPECT_THROW(safe_cast<int8_t>(std::numeric_limits<int16_t>::max()),
               std::overflow_error);
  EXPECT_THROW(safe_cast<int16_t>(std::numeric_limits<int32_t>::max()),
               std::overflow_error);
  EXPECT_THROW(safe_cast<int32_t>(std::numeric_limits<int64_t>::max()),
               std::overflow_error);

  EXPECT_THROW(safe_cast<uint8_t>(std::numeric_limits<uint16_t>::max()),
               std::overflow_error);
  EXPECT_THROW(safe_cast<uint16_t>(std::numeric_limits<uint32_t>::max()),
               std::overflow_error);
  EXPECT_THROW(safe_cast<uint32_t>(std::numeric_limits<uint64_t>::max()),
               std::overflow_error);
}

TEST(SafeCast, WidthUnderflow) {
  EXPECT_THROW(safe_cast<int8_t>(std::numeric_limits<int16_t>::min()),
               std::underflow_error);
  EXPECT_THROW(safe_cast<int16_t>(std::numeric_limits<int32_t>::min()),
               std::underflow_error);
  EXPECT_THROW(safe_cast<int32_t>(std::numeric_limits<int64_t>::min()),
               std::underflow_error);
}

TEST(SafeCast, UnsignedToSignedOverflow) {
  EXPECT_THROW(safe_cast<int8_t>(std::numeric_limits<uint8_t>::max()),
               std::overflow_error);
  EXPECT_THROW(safe_cast<int16_t>(std::numeric_limits<uint16_t>::max()),
               std::overflow_error);
  EXPECT_THROW(safe_cast<int32_t>(std::numeric_limits<uint32_t>::max()),
               std::overflow_error);
  EXPECT_THROW(safe_cast<int64_t>(std::numeric_limits<uint64_t>::max()),
               std::overflow_error);
}

TEST(SafeCast, SignedToUnsignedOverflow) {
  EXPECT_THROW(safe_cast<uint8_t>(std::numeric_limits<int16_t>::max()),
               std::overflow_error);
  EXPECT_THROW(safe_cast<uint16_t>(std::numeric_limits<int32_t>::max()),
               std::overflow_error);
  EXPECT_THROW(safe_cast<uint32_t>(std::numeric_limits<int64_t>::max()),
               std::overflow_error);
}

TEST(SafeCast, NoThrowOfSameTypes) {
  EXPECT_NO_THROW(safe_cast<int8_t>(std::numeric_limits<int8_t>::max()));
  EXPECT_NO_THROW(safe_cast<int8_t>(std::numeric_limits<int8_t>::min()));
  EXPECT_NO_THROW(safe_cast<uint8_t>(std::numeric_limits<uint8_t>::max()));
  EXPECT_NO_THROW(safe_cast<uint8_t>(std::numeric_limits<uint8_t>::min()));

  EXPECT_NO_THROW(safe_cast<int64_t>(std::numeric_limits<int64_t>::max()));
  EXPECT_NO_THROW(safe_cast<int64_t>(std::numeric_limits<int64_t>::min()));
  EXPECT_NO_THROW(safe_cast<uint64_t>(std::numeric_limits<uint64_t>::max()));
  EXPECT_NO_THROW(safe_cast<uint64_t>(std::numeric_limits<uint64_t>::min()));
}

TEST(SafeCast, BoundaryValues) {
  EXPECT_THROW(safe_cast<int8_t>(int64_t{-129}), std::underflow_error);
  EXPECT_NO_THROW(safe_cast<int8_t>(int64_t{-128}));
  EXPECT_NO_THROW(safe_cast<int8_t>(int64_t{0}));
  EXPECT_NO_THROW(safe_cast<int8_t>(int64_t{127}));
  EXPECT_THROW(safe_cast<int8_t>(int64_t{128}), std::overflow_error);

  EXPECT_NO_THROW(safe_cast<uint8_t>(255));
  EXPECT_THROW(safe_cast<uint8_t>(256), std::overflow_error);
  EXPECT_NO_THROW(safe_cast<int16_t>(-32768));
  EXPECT_THROW(safe_cast<int16_t>(-32769), std::underflow_error);
}

TEST(SafeCast, CorrectReturnType) {
  EXPECT_TRUE(
      (std::is_same_v<decltype(safe_cast<int8_t>(int64_t{42})), int8_t>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(safe_cast<int16_t>(uint64_t{42})), int16_t>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(safe_cast<int32_t>(int16_t{42})), int32_t>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(safe_cast<int64_t>(int16_t{42})), int64_t>));

  EXPECT_TRUE(
      (std::is_same_v<decltype(safe_cast<uint8_t>(int64_t{42})), uint8_t>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(safe_cast<uint16_t>(int8_t{42})), uint16_t>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(safe_cast<uint32_t>(int16_t{42})), uint32_t>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(safe_cast<uint64_t>(int16_t{42})), uint64_t>));
}

TEST(SafeCast, CheckValueOutput) {
  EXPECT_EQ(safe_cast<int8_t>(0), 0);
  EXPECT_EQ(safe_cast<uint8_t>(0), 0);
  EXPECT_EQ(safe_cast<int8_t>(1), 1);
  EXPECT_EQ(safe_cast<int8_t>(-1), -1);
  EXPECT_EQ(safe_cast<int32_t>(std::numeric_limits<int32_t>::max()),
            std::numeric_limits<int32_t>::max());
}
}  // namespace
}  // namespace sc
