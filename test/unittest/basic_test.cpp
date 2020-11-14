#include "atcoder/all"

#include <type_traits>

#include <gtest/gtest.h>

using namespace atcoder;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

#ifndef _MSC_VER

int mul100(int a) { return a * 100; }

TEST(BasicTest, UBSanitize) {
    int a = 1 << 30;
    ASSERT_DEATH(mul100(a), ".*");
}

#endif

#ifdef _MSC_VER

int main() {
    unsigned long long a = 123456789123456LL;
    unsigned long long b = 114514123456789LL;
    unsigned long long c;
    unsigned long long d = _umul128(a, b, &c);
    ASSERT_EQ(766397903ULL, c);
    ASSERT_EQ(15993528026429681536ULL, d);
}

#endif
