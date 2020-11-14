#include "atcoder/string"

#include <algorithm>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

using namespace atcoder;
using ll = long long;
using ull = unsigned long long;

std::vector<int> sa_naive(std::vector<int> s) {
    int n = int(s.size());
    std::vector<int> sa(n);
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](int l, int r) {
        return std::vector<int>{s.begin() + l, s.end()} <
               std::vector<int>{s.begin() + r, s.end()};
    });
    return sa;
}

std::vector<int> lcp_naive(std::vector<int> s, std::vector<int> sa) {
    int n = int(s.size());
    assert(n);
    std::vector<int> lcp(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int l = sa[i], r = sa[i + 1];
        while (l + lcp[i] < n && r + lcp[i] < n && s[l + lcp[i]] == s[r + lcp[i]]) lcp[i]++;
    }
    return lcp;
}

std::vector<int> z_naive(std::vector<int> s) {
    int n = int(s.size());    
    std::vector<int> z(n);
    for (int i = 0; i < n; i++) {
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    }
    return z;
}

TEST(StringTest, Empty) {
    ASSERT_EQ(std::vector<int>{}, suffix_array(""));
    ASSERT_EQ(std::vector<int>{}, suffix_array(std::vector<int>{}));

    ASSERT_EQ(std::vector<int>{}, z_algorithm(""));
    ASSERT_EQ(std::vector<int>{}, z_algorithm(std::vector<int>{}));
}

TEST(StringTest, SALCPNaive) {
    for (int n = 1; n <= 5; n++) {
        int m = 1;
        for (int i = 0; i < n; i++) m *= 4;
        for (int f = 0; f < m; f++) {
            std::vector<int> s(n);
            int g = f;
            int max_c = 0;
            for (int i = 0; i < n; i++) {
                s[i] = g % 4;
                max_c = std::max(max_c, s[i]);
                g /= 4;
            }
            auto sa = sa_naive(s);
            ASSERT_EQ(sa, suffix_array(s));
            ASSERT_EQ(sa, suffix_array(s, max_c));
            ASSERT_EQ(lcp_naive(s, sa), lcp_array(s, sa));
        }
    }
    for (int n = 1; n <= 10; n++) {
        int m = 1;
        for (int i = 0; i < n; i++) m *= 2;
        for (int f = 0; f < m; f++) {
            std::vector<int> s(n);
            int g = f;
            int max_c = 0;
            for (int i = 0; i < n; i++) {
                s[i] = g % 2;
                max_c = std::max(max_c, s[i]);
                g /= 2;
            }
            auto sa = sa_naive(s);
            ASSERT_EQ(sa, suffix_array(s));
            ASSERT_EQ(sa, suffix_array(s, max_c));
            ASSERT_EQ(lcp_naive(s, sa), lcp_array(s, sa));
        }
    }
}

TEST(StringTest, InternalSANaiveNaive) {
    for (int n = 1; n <= 5; n++) {
        int m = 1;
        for (int i = 0; i < n; i++) m *= 4;
        for (int f = 0; f < m; f++) {
            std::vector<int> s(n);
            int g = f;
            int max_c = 0;
            for (int i = 0; i < n; i++) {
                s[i] = g % 4;
                max_c = std::max(max_c, s[i]);
                g /= 4;
            }

            auto sa = internal::sa_naive(s);
            ASSERT_EQ(sa_naive(s), sa);
        }
    }
    for (int n = 1; n <= 10; n++) {
        int m = 1;
        for (int i = 0; i < n; i++) m *= 2;
        for (int f = 0; f < m; f++) {
            std::vector<int> s(n);
            int g = f;
            for (int i = 0; i < n; i++) {
                s[i] = g % 2;
                g /= 2;
            }

            auto sa = internal::sa_naive(s);
            ASSERT_EQ(sa_naive(s), sa);
        }
    }
}

TEST(StringTest, InternalSADoublingNaive) {
    for (int n = 1; n <= 5; n++) {
        int m = 1;
        for (int i = 0; i < n; i++) m *= 4;
        for (int f = 0; f < m; f++) {
            std::vector<int> s(n);
            int g = f;
            for (int i = 0; i < n; i++) {
                s[i] = g % 4;
                g /= 4;
            }

            auto sa = internal::sa_doubling(s);
            ASSERT_EQ(sa_naive(s), sa);
        }
    }
    for (int n = 1; n <= 10; n++) {
        int m = 1;
        for (int i = 0; i < n; i++) m *= 2;
        for (int f = 0; f < m; f++) {
            std::vector<int> s(n);
            int g = f;
            for (int i = 0; i < n; i++) {
                s[i] = g % 2;
                g /= 2;
            }

            auto sa = internal::sa_doubling(s);
            ASSERT_EQ(sa_naive(s), sa);
        }
    }
}

TEST(StringTest, InternalSAISNaive) {
    for (int n = 1; n <= 5; n++) {
        int m = 1;
        for (int i = 0; i < n; i++) m *= 4;
        for (int f = 0; f < m; f++) {
            std::vector<int> s(n);
            int g = f;
            int max_c = 0;
            for (int i = 0; i < n; i++) {
                s[i] = g % 4;
                max_c = std::max(max_c, s[i]);
                g /= 4;
            }
            
            auto sa = internal::sa_is<-1, -1>(s, max_c);
            ASSERT_EQ(sa_naive(s), sa);
        }
    }
    for (int n = 1; n <= 10; n++) {
        int m = 1;
        for (int i = 0; i < n; i++) m *= 2;
        for (int f = 0; f < m; f++) {
            std::vector<int> s(n);
            int g = f;
            int max_c = 0;
            for (int i = 0; i < n; i++) {
                s[i] = g % 2;
                max_c = std::max(max_c, s[i]);
                g /= 2;
            }

            auto sa = internal::sa_is<-1, -1>(s, max_c);
            ASSERT_EQ(sa_naive(s), sa);
        }
    }
}

TEST(StringTest, SAAllATest) {
    for (int n = 1; n <= 100; n++) {
        std::vector<int> s(n, 10);
        ASSERT_EQ(sa_naive(s), suffix_array(s));
        ASSERT_EQ(sa_naive(s), suffix_array(s, 10));
        ASSERT_EQ(sa_naive(s), suffix_array(s, 12));
    }
}

TEST(StringTest, SAAllABTest) {
    for (int n = 1; n <= 100; n++) {
        std::vector<int> s(n);
        for (int i = 0; i < n; i++) s[i] = (i % 2);
        ASSERT_EQ(sa_naive(s), suffix_array(s));
        ASSERT_EQ(sa_naive(s), suffix_array(s, 3));
    }
    for (int n = 1; n <= 100; n++) {
        std::vector<int> s(n);
        for (int i = 0; i < n; i++) s[i] = 1 - (i % 2);
        ASSERT_EQ(sa_naive(s), suffix_array(s));
        ASSERT_EQ(sa_naive(s), suffix_array(s, 3));
    }
}

TEST(StringTest, SA) {
    std::string s = "missisippi";

    std::vector<int> sa = suffix_array(s);

    std::vector<std::string> answer = {
        "i",           // 9
        "ippi",        // 6
        "isippi",      // 4
        "issisippi",   // 1
        "missisippi",  // 0
        "pi",          // 8
        "ppi",         // 7
        "sippi",       // 5
        "sisippi",     // 3
        "ssisippi",    // 2
    };

    ASSERT_EQ(answer.size(), sa.size());

    for (int i = 0; i < int(sa.size()); i++) {
        ASSERT_EQ(answer[i], s.substr(sa[i]));
    }
}

TEST(StringTest, SASingle) {
    ASSERT_EQ(std::vector<int>({0}), suffix_array(std::vector<int>{0}));
    ASSERT_EQ(std::vector<int>({0}), suffix_array(std::vector<int>{-1}));
    ASSERT_EQ(std::vector<int>({0}), suffix_array(std::vector<int>{1}));
    ASSERT_EQ(std::vector<int>({0}),
              suffix_array(std::vector<int>{std::numeric_limits<int>::min()}));
    ASSERT_EQ(std::vector<int>({0}),
              suffix_array(std::vector<int>{std::numeric_limits<int>::max()}));
}

TEST(StringTest, LCP) {
    std::string s = "aab";
    auto sa = suffix_array(s);
    ASSERT_EQ(std::vector<int>({0, 1, 2}), sa);
    auto lcp = lcp_array(s, sa);
    ASSERT_EQ(std::vector<int>({1, 0}), lcp);

    ASSERT_EQ(lcp, lcp_array(std::vector<int>({0, 0, 1}), sa));
    ASSERT_EQ(lcp, lcp_array(std::vector<int>({-100, -100, 100}), sa));
    ASSERT_EQ(lcp,
              lcp_array(std::vector<int>({std::numeric_limits<int>::min(),
                                          std::numeric_limits<int>::min(),
                                          std::numeric_limits<int>::max()}),
                        sa));

    ASSERT_EQ(lcp, lcp_array(std::vector<long long>(
                                 {std::numeric_limits<long long>::min(),
                                  std::numeric_limits<long long>::min(),
                                  std::numeric_limits<long long>::max()}),
                             sa));
    ASSERT_EQ(lcp, lcp_array(std::vector<unsigned int>(
                                 {std::numeric_limits<unsigned int>::min(),
                                  std::numeric_limits<unsigned int>::min(),
                                  std::numeric_limits<unsigned int>::max()}),
                             sa));
    ASSERT_EQ(lcp,
              lcp_array(std::vector<unsigned long long>(
                            {std::numeric_limits<unsigned long long>::min(),
                             std::numeric_limits<unsigned long long>::min(),
                             std::numeric_limits<unsigned long long>::max()}),
                        sa));
}

TEST(StringTest, ZAlgo) {
    std::string s = "abab";
    auto z = z_algorithm(s);
    ASSERT_EQ(std::vector<int>({4, 0, 2, 0}), z);
    ASSERT_EQ(std::vector<int>({4, 0, 2, 0}),
              z_algorithm(std::vector<int>{1, 10, 1, 10}));
    ASSERT_EQ(z_naive({0, 0, 0, 0, 0, 0, 0}), z_algorithm({0, 0, 0, 0, 0, 0, 0}));
}

TEST(StringTest, ZNaive) {
    for (int n = 1; n <= 6; n++) {
        int m = 1;
        for (int i = 0; i < n; i++) m *= 4;
        for (int f = 0; f < m; f++) {
            std::vector<int> s(n);
            int g = f;
            for (int i = 0; i < n; i++) {
                s[i] = g % 4;
                g /= 4;
            }
            ASSERT_EQ(z_naive(s), z_algorithm(s));
        }
    }
    for (int n = 1; n <= 10; n++) {
        int m = 1;
        for (int i = 0; i < n; i++) m *= 2;
        for (int f = 0; f < m; f++) {
            std::vector<int> s(n);
            int g = f;
            for (int i = 0; i < n; i++) {
                s[i] = g % 2;
                g /= 2;
            }
            ASSERT_EQ(z_naive(s), z_algorithm(s));
        }
    }
}
