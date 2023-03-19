#include "atcoder/internal_bit"

#include <numeric>

#include <gtest/gtest.h>

using namespace atcoder;
using ll = long long;
using ull = unsigned long long;

TEST(BitTest, BitCeil) {
    ASSERT_EQ(1, internal::bit_ceil(0U));
    ASSERT_EQ(1, internal::bit_ceil(1U));
    ASSERT_EQ(2, internal::bit_ceil(2U));
    ASSERT_EQ(4, internal::bit_ceil(3U));
    ASSERT_EQ(4, internal::bit_ceil(4U));
    ASSERT_EQ(8, internal::bit_ceil(5U));
    ASSERT_EQ(8, internal::bit_ceil(6U));
    ASSERT_EQ(8, internal::bit_ceil(7U));
    ASSERT_EQ(8, internal::bit_ceil(8U));
    ASSERT_EQ(16, internal::bit_ceil(9U));
    ASSERT_EQ(1U << 30, internal::bit_ceil(1U << 30));
    ASSERT_EQ(1U << 31, internal::bit_ceil((1U << 30) + 1));
    ASSERT_EQ(1U << 31, internal::bit_ceil((1U << 31) - 1));
    ASSERT_EQ(1U << 31, internal::bit_ceil(1U << 31));
}

TEST(BitTest, CountrZero) {
    ASSERT_EQ(0, internal::countr_zero(1U));
    ASSERT_EQ(1, internal::countr_zero(2U));
    ASSERT_EQ(0, internal::countr_zero(3U));
    ASSERT_EQ(2, internal::countr_zero(4U));
    ASSERT_EQ(0, internal::countr_zero(5U));
    ASSERT_EQ(1, internal::countr_zero(6U));
    ASSERT_EQ(0, internal::countr_zero(7U));
    ASSERT_EQ(3, internal::countr_zero(8U));
    ASSERT_EQ(0, internal::countr_zero(9U));
    ASSERT_EQ(30, internal::countr_zero(1U << 30));
    ASSERT_EQ(0, internal::countr_zero((1U << 31) - 1));
    ASSERT_EQ(31, internal::countr_zero(1U << 31));
    ASSERT_EQ(0, internal::countr_zero(std::numeric_limits<unsigned int>::max()));
}

TEST(BitTest, CountrZeroConstexpr) {
    ASSERT_EQ(0, internal::countr_zero_constexpr(1U));
    ASSERT_EQ(1, internal::countr_zero_constexpr(2U));
    ASSERT_EQ(0, internal::countr_zero_constexpr(3U));
    ASSERT_EQ(2, internal::countr_zero_constexpr(4U));
    ASSERT_EQ(0, internal::countr_zero_constexpr(5U));
    ASSERT_EQ(1, internal::countr_zero_constexpr(6U));
    ASSERT_EQ(0, internal::countr_zero_constexpr(7U));
    ASSERT_EQ(3, internal::countr_zero_constexpr(8U));
    ASSERT_EQ(0, internal::countr_zero_constexpr(9U));
    ASSERT_EQ(30, internal::countr_zero_constexpr(1U << 30));
    ASSERT_EQ(0, internal::countr_zero_constexpr((1U << 31) - 1));
    ASSERT_EQ(31, internal::countr_zero_constexpr(1U << 31));
    ASSERT_EQ(0,
              internal::countr_zero_constexpr(std::numeric_limits<unsigned int>::max()));
}
