#include "atcoder/modint"

#include <type_traits>

#include <gtest/gtest.h>

using namespace atcoder;
using ll = long long;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

static_assert(internal::is_modint<static_modint<1>>::value, "");
static_assert(internal::is_modint<static_modint<998244353>>::value, "");
static_assert(internal::is_modint<modint>::value, "");
static_assert(internal::is_modint<dynamic_modint<0>>::value, "");
static_assert(!internal::is_modint<int>::value, "");

static_assert(internal::is_static_modint<static_modint<1>>::value, "");
static_assert(internal::is_static_modint<static_modint<998244353>>::value, "");
static_assert(internal::is_static_modint<modint998244353>::value, "");
static_assert(internal::is_static_modint<modint1000000007>::value, "");
static_assert(!internal::is_static_modint<modint>::value, "");
static_assert(!internal::is_static_modint<dynamic_modint<0>>::value, "");
static_assert(!internal::is_static_modint<int>::value, "");

static_assert(!internal::is_dynamic_modint<static_modint<1>>::value, "");
static_assert(!internal::is_dynamic_modint<static_modint<998244353>>::value,
              "");
static_assert(internal::is_dynamic_modint<modint>::value, "");
static_assert(internal::is_dynamic_modint<dynamic_modint<0>>::value, "");
static_assert(!internal::is_dynamic_modint<int>::value, "");

static_assert(std::is_same<modint, dynamic_modint<-1>>::value, "");

static_assert(modint998244353::mod() == 998244353, "");
static_assert(modint1000000007::mod() == 1000000007, "");

TEST(ModintTest, DynamicBorder) {
    using mint = modint;
    const int mod_upper = std::numeric_limits<int>::max();
    for (unsigned int mod = mod_upper; mod >= mod_upper - 20; mod--) {
        mint::set_mod(mod);
        std::vector<ll> v;
        for (int i = 0; i < 10; i++) {
            v.push_back(i);
            v.push_back(mod - i);
            v.push_back(mod / 2 + i);
            v.push_back(mod / 2 - i);
        }
        for (ll a : v) {
            ASSERT_EQ(((a * a) % mod * a) % mod, (mint(a).pow(3)).val());
            for (ll b : v) {
                ASSERT_EQ((a + b) % mod, (mint(a) + mint(b)).val());
                ASSERT_EQ((a - b + mod) % mod, (mint(a) - mint(b)).val());
                ASSERT_EQ((a * b) % mod, (mint(a) * mint(b)).val());
            }
        }
    }
}

TEST(ModintTest, ULL) {
    modint::set_mod(998244353);
    ASSERT_NE(modint::mod() - 1, modint((unsigned long long)(-1)).val());
    ASSERT_NE(0, ((unsigned long long)(-1) + modint(1)).val());
    using mint = static_modint<998244353>;
    ASSERT_NE(mint::mod() - 1, modint((unsigned long long)(-1)).val());
    ASSERT_NE(0, ((unsigned long long)(-1) + mint(1)).val());
}

TEST(ModintTest, Mod1) {
    modint::set_mod(1);
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ASSERT_EQ((modint(i) * modint(j)).val(), 0);
        }
    }
    ASSERT_EQ((modint(1234) + modint(5678)).val(), 0);
    ASSERT_EQ((modint(1234) - modint(5678)).val(), 0);
    ASSERT_EQ((modint(1234) * modint(5678)).val(), 0);
    ASSERT_EQ((modint(1234).pow(5678)), 0);
    ASSERT_EQ(0, modint(0).inv());

    ASSERT_EQ(0, modint(true).val());

    using mint = static_modint<1>;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ASSERT_EQ((mint(i) * mint(j)).val(), 0);
        }
    }
    ASSERT_EQ((mint(1234) + mint(5678)).val(), 0);
    ASSERT_EQ((mint(1234) - mint(5678)).val(), 0);
    ASSERT_EQ((mint(1234) * mint(5678)).val(), 0);
    ASSERT_EQ((mint(1234).pow(5678)), 0);
    ASSERT_EQ(0, modint(0).inv());

    ASSERT_EQ(0, mint(true).val());
}

TEST(ModintTest, ModIntMax) {
    modint::set_mod(INT32_MAX);
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ASSERT_EQ((modint(i) * modint(j)).val(), i * j);
        }
    }
    ASSERT_EQ((modint(1234) + modint(5678)).val(), 1234 + 5678);
    ASSERT_EQ((modint(1234) - modint(5678)).val(), INT32_MAX - 5678 + 1234);
    ASSERT_EQ((modint(1234) * modint(5678)).val(), 1234 * 5678);

    using mint = static_modint<INT32_MAX>;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ASSERT_EQ((mint(i) * mint(j)).val(), i * j);
        }
    }
    ASSERT_EQ((mint(1234) + mint(5678)).val(), 1234 + 5678);
    ASSERT_EQ((mint(1234) - mint(5678)).val(), INT32_MAX - 5678 + 1234);
    ASSERT_EQ((mint(1234) * mint(5678)).val(), 1234 * 5678);
    ASSERT_EQ((mint(INT32_MAX) + mint(INT32_MAX)).val(), 0);
}

#ifndef _MSC_VER

TEST(ModintTest, Int128) {
    modint::set_mod(998244353);
    ASSERT_EQ(12345678, modint(__int128_t(12345678)).val());
    ASSERT_EQ(12345678, modint(__uint128_t(12345678)).val());
    ASSERT_EQ(12345678, modint(__int128(12345678)).val());
    ASSERT_EQ(12345678, modint((unsigned __int128)(12345678)).val());
    ASSERT_EQ(modint(2).pow(100).val(), modint(__int128_t(1) << 100).val());
    ASSERT_EQ(modint(2).pow(100).val(), modint(__uint128_t(1) << 100).val());
    using mint = static_modint<998244353>;
    ASSERT_EQ(12345678, mint(__int128_t(12345678)).val());
    ASSERT_EQ(12345678, mint(__uint128_t(12345678)).val());
    ASSERT_EQ(12345678, mint(__int128(12345678)).val());
    ASSERT_EQ(12345678, mint((unsigned __int128)(12345678)).val());
    ASSERT_EQ(mint(2).pow(100).val(), mint(__int128_t(1) << 100).val());
    ASSERT_EQ(mint(2).pow(100).val(), mint(__uint128_t(1) << 100).val());
}

#endif

TEST(ModintTest, Inv) {
    for (int i = 1; i < 10; i++) {
        int x = static_modint<11>(i).inv().val();
        ASSERT_EQ(1, (x * i) % 11);
    }

    for (int i = 1; i < 11; i++) {
        if (gcd(i, 12) != 1) continue;
        int x = static_modint<12>(i).inv().val();
        ASSERT_EQ(1, (x * i) % 12);
    }

    for (int i = 1; i < 100000; i++) {
        int x = static_modint<1'000'000'007>(i).inv().val();
        ASSERT_EQ(1, (ll(x) * i) % 1'000'000'007);
    }

    for (int i = 1; i < 100000; i++) {
        if (gcd(i, 1'000'000'008) != 1) continue;
        int x = static_modint<1'000'000'008>(i).inv().val();
        ASSERT_EQ(1, (ll(x) * i) % 1'000'000'008);
    }

    modint::set_mod(998244353);
    for (int i = 1; i < 100000; i++) {
        int x = modint(i).inv().val();
        ASSERT_LE(0, x);
        ASSERT_GE(998244353 - 1, x);
        ASSERT_EQ(1, (ll(x) * i) % 998244353);
    }

    modint::set_mod(1'000'000'008);
    for (int i = 1; i < 100000; i++) {
        if (gcd(i, 1'000'000'008) != 1) continue;
        int x = modint(i).inv().val();
        ASSERT_EQ(1, (ll(x) * i) % 1'000'000'008);
    }

    modint::set_mod(INT32_MAX);
    for (int i = 1; i < 100000; i++) {
        if (gcd(i, INT32_MAX) != 1) continue;
        int x = modint(i).inv().val();
        ASSERT_EQ(1, (ll(x) * i) % INT32_MAX);
    }
}

TEST(ModintTest, ConstUsage) {
    using sint = static_modint<11>;
    const sint a = 9;
    ASSERT_EQ(9, a.val());
    using dint = modint;
    dint::set_mod(11);
    const dint b = 9;
    ASSERT_EQ(9, b.val());
}

TEST(ModintTest, Increment) {
    using sint = static_modint<11>;
    using dint = modint;
    dint::set_mod(11);

    {
        sint a;
        a = 8;
        ASSERT_EQ(9, (++a).val());
        ASSERT_EQ(10, (++a).val());
        ASSERT_EQ(0, (++a).val());
        ASSERT_EQ(1, (++a).val());
        a = 3;
        ASSERT_EQ(2, (--a).val());
        ASSERT_EQ(1, (--a).val());
        ASSERT_EQ(0, (--a).val());
        ASSERT_EQ(10, (--a).val());
        a = 8;
        ASSERT_EQ(8, (a++).val());
        ASSERT_EQ(9, (a++).val());
        ASSERT_EQ(10, (a++).val());
        ASSERT_EQ(0, (a++).val());
        ASSERT_EQ(1, a.val());
        a = 3;
        ASSERT_EQ(3, (a--).val());
        ASSERT_EQ(2, (a--).val());
        ASSERT_EQ(1, (a--).val());
        ASSERT_EQ(0, (a--).val());
        ASSERT_EQ(10, a.val());
    }
    {
        dint a;
        a = 8;
        ASSERT_EQ(9, (++a).val());
        ASSERT_EQ(10, (++a).val());
        ASSERT_EQ(0, (++a).val());
        ASSERT_EQ(1, (++a).val());
        a = 3;
        ASSERT_EQ(2, (--a).val());
        ASSERT_EQ(1, (--a).val());
        ASSERT_EQ(0, (--a).val());
        ASSERT_EQ(10, (--a).val());
        a = 8;
        ASSERT_EQ(8, (a++).val());
        ASSERT_EQ(9, (a++).val());
        ASSERT_EQ(10, (a++).val());
        ASSERT_EQ(0, (a++).val());
        ASSERT_EQ(1, a.val());
        a = 3;
        ASSERT_EQ(3, (a--).val());
        ASSERT_EQ(2, (a--).val());
        ASSERT_EQ(1, (a--).val());
        ASSERT_EQ(0, (a--).val());
        ASSERT_EQ(10, a.val());
    }
}

TEST(ModintTest, StaticUsage) {
    using mint = static_modint<11>;
    ASSERT_EQ(11, mint::mod());
    ASSERT_EQ(4, +mint(4));
    ASSERT_EQ(7, -mint(4));

    ASSERT_FALSE(mint(1) == mint(3));
    ASSERT_TRUE(mint(1) != mint(3));
    ASSERT_TRUE(mint(1) == mint(12));
    ASSERT_FALSE(mint(1) != mint(12));

    EXPECT_DEATH(mint(3).pow(-1), ".*");
}

TEST(ModintTest, DynamicUsage) {
    ASSERT_EQ(998244353, dynamic_modint<12345>::mod());
    using mint = modint;
    mint::set_mod(998244353);
    ASSERT_EQ(998244353, mint::mod());
    ASSERT_EQ(3, (mint(1) + mint(2)).val());
    ASSERT_EQ(3, (1 + mint(2)).val());
    ASSERT_EQ(3, (mint(1) + 2).val());

    mint::set_mod(3);
    ASSERT_EQ(3, mint::mod());
    ASSERT_EQ(1, (mint(2) - mint(1)).val());
    ASSERT_EQ(0, (mint(1) + mint(2)).val());

    mint::set_mod(11);
    ASSERT_EQ(11, mint::mod());
    ASSERT_EQ(4, (mint(3) * mint(5)).val());

    ASSERT_EQ(4, +mint(4));
    ASSERT_EQ(7, -mint(4));

    ASSERT_FALSE(mint(1) == mint(3));
    ASSERT_TRUE(mint(1) != mint(3));
    ASSERT_TRUE(mint(1) == mint(12));
    ASSERT_FALSE(mint(1) != mint(12));

    EXPECT_DEATH(mint(3).pow(-1), ".*");
}

TEST(ModintTest, Constructor) {
    modint::set_mod(11);
    ASSERT_EQ(1, modint(true).val());
    ASSERT_EQ(3, modint((char)(3)).val());
    ASSERT_EQ(3, modint((signed char)(3)).val());
    ASSERT_EQ(3, modint((unsigned char)(3)).val());
    ASSERT_EQ(3, modint((short)(3)).val());
    ASSERT_EQ(3, modint((unsigned short)(3)).val());
    ASSERT_EQ(3, modint((int)(3)).val());
    ASSERT_EQ(3, modint((unsigned int)(3)).val());
    ASSERT_EQ(3, modint((long)(3)).val());
    ASSERT_EQ(3, modint((unsigned long)(3)).val());
    ASSERT_EQ(3, modint((long long)(3)).val());
    ASSERT_EQ(3, modint((unsigned long long)(3)).val());
    ASSERT_EQ(1, modint((signed char)(-10)).val());
    ASSERT_EQ(1, modint((short)(-10)).val());
    ASSERT_EQ(1, modint((int)(-10)).val());
    ASSERT_EQ(1, modint((long)(-10)).val());
    ASSERT_EQ(1, modint((long long)(-10)).val());

    ASSERT_EQ(2, (int(1) + modint(1)).val());
    ASSERT_EQ(2, (short(1) + modint(1)).val());

    modint m;
    ASSERT_EQ(0, m.val());
}

TEST(ModintTest, ConstructorStatic) {
    using mint = static_modint<11>;
    ASSERT_EQ(1, mint(true).val());
    ASSERT_EQ(3, mint((char)(3)).val());
    ASSERT_EQ(3, mint((signed char)(3)).val());
    ASSERT_EQ(3, mint((unsigned char)(3)).val());
    ASSERT_EQ(3, mint((short)(3)).val());
    ASSERT_EQ(3, mint((unsigned short)(3)).val());
    ASSERT_EQ(3, mint((int)(3)).val());
    ASSERT_EQ(3, mint((unsigned int)(3)).val());
    ASSERT_EQ(3, mint((long)(3)).val());
    ASSERT_EQ(3, mint((unsigned long)(3)).val());
    ASSERT_EQ(3, mint((long long)(3)).val());
    ASSERT_EQ(3, mint((unsigned long long)(3)).val());
    ASSERT_EQ(1, mint((signed char)(-10)).val());
    ASSERT_EQ(1, mint((short)(-10)).val());
    ASSERT_EQ(1, mint((int)(-10)).val());
    ASSERT_EQ(1, mint((long)(-10)).val());
    ASSERT_EQ(1, mint((long long)(-10)).val());

    ASSERT_EQ(2, (int(1) + mint(1)).val());
    ASSERT_EQ(2, (short(1) + mint(1)).val());

    mint m;
    ASSERT_EQ(0, m.val());
}
