#include "safe_cast.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

namespace sc {
namespace {
class SafeCast : public ::testing::Test {
 protected:
  uint8_t const maxuint8 = std::numeric_limits<uint8_t>::max();
  uint16_t const maxuint16 = std::numeric_limits<uint16_t>::max();
  uint32_t const maxuint32 = std::numeric_limits<uint32_t>::max();
  uint64_t const maxuint64 = std::numeric_limits<uint64_t>::max();

  uint8_t const minuint8 = std::numeric_limits<uint8_t>::min();
  uint16_t const minuint16 = std::numeric_limits<uint16_t>::min();
  uint32_t const minuint32 = std::numeric_limits<uint32_t>::min();
  uint64_t const minuint64 = std::numeric_limits<uint64_t>::min();

  int8_t const maxint8 = std::numeric_limits<int8_t>::max();
  int16_t const maxint16 = std::numeric_limits<int16_t>::max();
  int32_t const maxint32 = std::numeric_limits<int32_t>::max();
  int64_t const maxint64 = std::numeric_limits<int64_t>::max();

  int8_t const minint8 = std::numeric_limits<int8_t>::min();
  int16_t const minint16 = std::numeric_limits<int16_t>::min();
  int32_t const minint32 = std::numeric_limits<int32_t>::min();
  int64_t const minint64 = std::numeric_limits<int64_t>::min();
};

TEST_F(SafeCast, CastUint8t) {
  EXPECT_NO_THROW(safe_cast<uint8_t>(std::numeric_limits<uint8_t>::max()));
  EXPECT_THROW(safe_cast<uint8_t>(maxuint16), std::overflow_error);
  EXPECT_THROW(safe_cast<uint8_t>(maxuint32), std::overflow_error);
  EXPECT_THROW(safe_cast<uint8_t>(maxuint64), std::overflow_error);

  EXPECT_NO_THROW(safe_cast<uint8_t>(maxint8));
  EXPECT_THROW(safe_cast<uint8_t>(maxint16), std::overflow_error);
  EXPECT_THROW(safe_cast<uint8_t>(maxint32), std::overflow_error);
  EXPECT_THROW(safe_cast<uint8_t>(maxint64), std::overflow_error);

  EXPECT_NO_THROW(safe_cast<uint8_t>(minuint8));
  EXPECT_NO_THROW(safe_cast<uint8_t>(minuint16));
  EXPECT_NO_THROW(safe_cast<uint8_t>(minuint32));
  EXPECT_NO_THROW(safe_cast<uint8_t>(minuint64));

  EXPECT_THROW(safe_cast<uint8_t>(minint8), std::underflow_error);
  EXPECT_THROW(safe_cast<uint8_t>(minint16), std::underflow_error);
  EXPECT_THROW(safe_cast<uint8_t>(minint32), std::underflow_error);
  EXPECT_THROW(safe_cast<uint8_t>(minint64), std::underflow_error);
}

TEST_F(SafeCast, CastUint16t) {
  EXPECT_NO_THROW(safe_cast<uint16_t>(maxuint8));
  EXPECT_NO_THROW(safe_cast<uint16_t>(maxuint16));
  EXPECT_THROW(safe_cast<uint16_t>(maxuint32), std::overflow_error);
  EXPECT_THROW(safe_cast<uint16_t>(maxuint64), std::overflow_error);

  EXPECT_NO_THROW(safe_cast<uint16_t>(minuint8));
  EXPECT_NO_THROW(safe_cast<uint16_t>(minuint16));
  EXPECT_NO_THROW(safe_cast<uint16_t>(minuint32));
  EXPECT_NO_THROW(safe_cast<uint16_t>(minuint64));

  EXPECT_NO_THROW(safe_cast<uint16_t>(maxint8));
  EXPECT_NO_THROW(safe_cast<uint16_t>(maxint16));
  EXPECT_THROW(safe_cast<uint16_t>(maxint32), std::overflow_error);
  EXPECT_THROW(safe_cast<uint16_t>(maxint64), std::overflow_error);

  EXPECT_THROW(safe_cast<uint16_t>(minint8), std::underflow_error);
  EXPECT_THROW(safe_cast<uint16_t>(minint16), std::underflow_error);
  EXPECT_THROW(safe_cast<uint16_t>(minint32), std::underflow_error);
  EXPECT_THROW(safe_cast<uint16_t>(minint64), std::underflow_error);
}

TEST_F(SafeCast, CastUint32t) {
  EXPECT_NO_THROW(safe_cast<uint32_t>(maxuint8));
  EXPECT_NO_THROW(safe_cast<uint32_t>(maxuint16));
  EXPECT_NO_THROW(safe_cast<uint32_t>(maxuint32));
  EXPECT_THROW(safe_cast<uint32_t>(maxuint64), std::overflow_error);

  EXPECT_NO_THROW(safe_cast<uint32_t>(minuint8));
  EXPECT_NO_THROW(safe_cast<uint32_t>(minuint16));
  EXPECT_NO_THROW(safe_cast<uint32_t>(minuint32));
  EXPECT_NO_THROW(safe_cast<uint32_t>(minuint64));

  EXPECT_NO_THROW(safe_cast<uint32_t>(maxint8));
  EXPECT_NO_THROW(safe_cast<uint32_t>(maxint16));
  EXPECT_NO_THROW(safe_cast<uint32_t>(maxint32));
  EXPECT_THROW(safe_cast<uint32_t>(maxint64), std::overflow_error);

  EXPECT_THROW(safe_cast<uint32_t>(minint8), std::underflow_error);
  EXPECT_THROW(safe_cast<uint32_t>(minint16), std::underflow_error);
  EXPECT_THROW(safe_cast<uint32_t>(minint32), std::underflow_error);
  EXPECT_THROW(safe_cast<uint32_t>(minint64), std::underflow_error);
}

TEST_F(SafeCast, CastUint64t) {
  EXPECT_NO_THROW(safe_cast<uint64_t>(maxuint8));
  EXPECT_NO_THROW(safe_cast<uint64_t>(maxuint16));
  EXPECT_NO_THROW(safe_cast<uint64_t>(maxuint32));
  EXPECT_NO_THROW(safe_cast<uint64_t>(maxuint64));

  EXPECT_NO_THROW(safe_cast<uint64_t>(minuint8));
  EXPECT_NO_THROW(safe_cast<uint64_t>(minuint16));
  EXPECT_NO_THROW(safe_cast<uint64_t>(minuint32));
  EXPECT_NO_THROW(safe_cast<uint64_t>(minuint64));

  EXPECT_NO_THROW(safe_cast<uint64_t>(maxint8));
  EXPECT_NO_THROW(safe_cast<uint64_t>(maxint16));
  EXPECT_NO_THROW(safe_cast<uint64_t>(maxint32));
  EXPECT_NO_THROW(safe_cast<uint64_t>(maxint64));

  EXPECT_THROW(safe_cast<uint64_t>(minint8), std::underflow_error);
  EXPECT_THROW(safe_cast<uint64_t>(minint16), std::underflow_error);
  EXPECT_THROW(safe_cast<uint64_t>(minint32), std::underflow_error);
  EXPECT_THROW(safe_cast<uint64_t>(minint64), std::underflow_error);
}

TEST_F(SafeCast, CastInt8t) {
  EXPECT_NO_THROW(safe_cast<int8_t>(maxint8));
  EXPECT_THROW(safe_cast<int8_t>(maxint16), std::overflow_error);
  EXPECT_THROW(safe_cast<int8_t>(maxint32), std::overflow_error);
  EXPECT_THROW(safe_cast<int8_t>(maxint64), std::overflow_error);

  EXPECT_NO_THROW(safe_cast<int8_t>(minint8));
  EXPECT_THROW(safe_cast<int8_t>(minint16), std::underflow_error);
  EXPECT_THROW(safe_cast<int8_t>(minint32), std::underflow_error);
  EXPECT_THROW(safe_cast<int8_t>(minint64), std::underflow_error);

  EXPECT_NO_THROW(safe_cast<int8_t>(minuint8));
  EXPECT_THROW(safe_cast<int8_t>(maxuint8), std::overflow_error);
  EXPECT_THROW(safe_cast<int8_t>(maxuint16), std::overflow_error);
  EXPECT_THROW(safe_cast<int8_t>(maxuint32), std::overflow_error);
  EXPECT_THROW(safe_cast<int8_t>(maxuint64), std::overflow_error);
}

/*
TEST(SafeCast, CastInt8t) {
    int8_t val = 127;
    int16_t overval = 128;
    int16_t underval = -129;

    EXPECT_NO_THROW(safe_cast<int8_t>(val));
    EXPECT_THROW(safe_cast<int8_t>(overval), std::overflow_error);
    EXPECT_THROW(safe_cast<int8_t>(underval), std::underflow_error);
}

TEST(SafeCast, CastUint16t) {
    uint16_t constexpr  val = 65535U;
    uint32_t constexpr overval = 65536U;
    int32_t constexpr underval = -1;

    EXPECT_NO_THROW(safe_cast<uint16_t>(val));
    EXPECT_THROW(safe_cast<uint16_t>(overval), std::overflow_error);
    EXPECT_THROW(safe_cast<uint16_t>(underval), std::underflow_error);
}

TEST(SafeCast, CastInt16t) {
    int16_t constexpr val = 32767;
    int32_t constexpr overval = 32768;
    int32_t constexpr  underval = -32769;

    EXPECT_NO_THROW(safe_cast<int16_t>(val));
    EXPECT_THROW(safe_cast<int16_t>(overval), std::overflow_error);
    EXPECT_THROW(safe_cast<int16_t>(underval), std::underflow_error);
}

TEST(SafeCast, CastUint32t) {
    uint32_t constexpr val = 4294967295U;
    uint64_t constexpr overval = 4294967296ULL;
    int64_t constexpr underval = -1LL;

    EXPECT_NO_THROW(safe_cast<uint32_t>(val));
    EXPECT_THROW(safe_cast<uint32_t>(overval), std::overflow_error);
    EXPECT_THROW(safe_cast<uint32_t>(underval), std::underflow_error);
}

TEST(SafeCast, CastInt32t) {
    int32_t constexpr val = 2147483647;
    int64_t constexpr overval = 2147483648LL;
    int64_t constexpr underval = -2147483649LL;

    EXPECT_NO_THROW(safe_cast<int32_t>(val));
    EXPECT_THROW(safe_cast<int32_t>(overval), std::overflow_error);
    EXPECT_THROW(safe_cast<int32_t>(underval), std::underflow_error);
}

TEST(SafeCast, CastUint64t) {
    uint64_t constexpr val = std::numeric_limits<uint64_t>::max();
    int64_t constexpr underval = -1LL;

    EXPECT_NO_THROW(safe_cast<uint64_t>(val));
    EXPECT_THROW(safe_cast<uint64_t>(underval), std::underflow_error);
}

TEST(SafeCast, CastInt64t) {
    int64_t constexpr val = std::numeric_limits<int64_t>::max();
    uint64_t constexpr overval =
static_cast<uint64_t>(std::numeric_limits<int64_t>::max()) + 1;

    EXPECT_NO_THROW(safe_cast<int64_t>(val));
    EXPECT_THROW(safe_cast<int64_t>(overval), std::overflow_error);
}

TEST(SafeCast, CastBetweenSignedAndUnsigned) {
    int32_t constexpr signed_val = -1;
    uint32_t constexpr unsigned_val = 0xFFFFFFFF;

    EXPECT_THROW(safe_cast<uint32_t>(signed_val), std::underflow_error);
    EXPECT_THROW(safe_cast<int32_t>(unsigned_val), std::overflow_error);
}

TEST(SafeCast, CastToSmallerUnsignedType) {
    uint32_t constexpr large_val = 1000000;
    uint16_t constexpr small_val = 1000;

    EXPECT_THROW(safe_cast<uint16_t>(large_val), std::overflow_error);
    EXPECT_NO_THROW(safe_cast<uint16_t>(small_val));
}

TEST(SafeCast, CastToSmallerSignedType) {
    int32_t constexpr large_positive = 100000;
    int32_t constexpr large_negative = -100000;
    int16_t constexpr  small_val = 1000;

    EXPECT_THROW(safe_cast<int16_t>(large_positive), std::overflow_error);
    EXPECT_THROW(safe_cast<int16_t>(large_negative), std::underflow_error);
    EXPECT_NO_THROW(safe_cast<int16_t>(small_val));
}

TEST(SafeCast, EdgeCases) {
    EXPECT_NO_THROW(safe_cast<int8_t>(std::numeric_limits<int8_t>::min()));
    EXPECT_NO_THROW(safe_cast<int8_t>(std::numeric_limits<int8_t>::max()));
    EXPECT_NO_THROW(safe_cast<uint8_t>(std::numeric_limits<uint8_t>::max()));
    EXPECT_NO_THROW(safe_cast<uint8_t>(std::numeric_limits<uint8_t>::min()));
}

TEST(SafeCast, CorrectValues) {
    EXPECT_EQ(safe_cast<int16_t>(32767), 32767);
    EXPECT_EQ(safe_cast<uint16_t>(65535U), 65535U);
    EXPECT_EQ(safe_cast<int32_t>(-1), -1);
    EXPECT_EQ(safe_cast<uint32_t>(4294967295U), 4294967295U);
}

TEST(SafeCast, SameTypeCast) {
    EXPECT_EQ(safe_cast<int32_t>(42), 42);
    EXPECT_EQ(safe_cast<uint64_t>(18446744073709551615ULL),
18446744073709551615ULL);
}
*/
}  // namespace
}  // namespace sc
