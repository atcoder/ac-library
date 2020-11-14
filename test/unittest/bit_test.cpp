#include "atcoder/internal_bit"

#include <numeric>

#include <gtest/gtest.h>

using namespace atcoder;
using ll = long long;
using ull = unsigned long long;

TEST(BitTest, CeilPow2) {
    ASSERT_EQ(0, internal::ceil_pow2(0));
    ASSERT_EQ(0, internal::ceil_pow2(1));
    ASSERT_EQ(1, internal::ceil_pow2(2));
    ASSERT_EQ(2, internal::ceil_pow2(3));
    ASSERT_EQ(2, internal::ceil_pow2(4));
    ASSERT_EQ(3, internal::ceil_pow2(5));
    ASSERT_EQ(3, internal::ceil_pow2(6));
    ASSERT_EQ(3, internal::ceil_pow2(7));
    ASSERT_EQ(3, internal::ceil_pow2(8));
    ASSERT_EQ(4, internal::ceil_pow2(9));
    ASSERT_EQ(30, internal::ceil_pow2(1 << 30));
    ASSERT_EQ(31, internal::ceil_pow2((1 << 30) + 1));
    ASSERT_EQ(31, internal::ceil_pow2(std::numeric_limits<int>::max()));
}

TEST(BitTest, BSF) {
    ASSERT_EQ(0, internal::bsf(1));
    ASSERT_EQ(1, internal::bsf(2));
    ASSERT_EQ(0, internal::bsf(3));
    ASSERT_EQ(2, internal::bsf(4));
    ASSERT_EQ(0, internal::bsf(5));
    ASSERT_EQ(1, internal::bsf(6));
    ASSERT_EQ(0, internal::bsf(7));
    ASSERT_EQ(3, internal::bsf(8));
    ASSERT_EQ(0, internal::bsf(9));
    ASSERT_EQ(30, internal::bsf(1U << 30));
    ASSERT_EQ(0, internal::bsf((1U << 31) - 1));
    ASSERT_EQ(31, internal::bsf(1U << 31));
    ASSERT_EQ(0, internal::bsf(std::numeric_limits<unsigned int>::max()));
}
