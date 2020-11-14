#include "atcoder/lazysegtree"

#include "../utils/random.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include <gtest/gtest.h>

using namespace atcoder;

// time manager
struct time_manager {
    std::vector<int> v;
    time_manager(int n) : v(n, -1) {}
    void action(int l, int r, int time) {
        for (int i = l; i < r; i++) {
            v[i] = time;
        }
    }
    int prod(int l, int r) {
        int res = -1;
        for (int i = l; i < r; i++) {
            res = std::max(res, v[i]);
        }
        return res;
    }
};

struct S {
    int l, r, time;
};

struct T {
    int new_time;
};

S op_ss(S l, S r) {
    if (l.l == -1) return r;
    if (r.l == -1) return l;
    assert(l.r == r.l);
    return S{l.l, r.r, std::max(l.time, r.time)};
}

S op_ts(T l, S r) {
    if (l.new_time == -1) return r;
    assert(r.time < l.new_time);
    return S{r.l, r.r, l.new_time};
}

T op_tt(T l, T r) {
    if (l.new_time == -1) return r;
    if (r.new_time == -1) return l;
    assert(l.new_time > r.new_time);
    return l;
}

S e_s() { return S{-1, -1, -1}; }

T e_t() { return T{-1}; }

using seg = lazy_segtree<S, op_ss, e_s, T, op_ts, op_tt, e_t>;

TEST(LazySegtreeStressTest, NaiveTest) {
    for (int n = 1; n <= 30; n++) {
        for (int ph = 0; ph < 10; ph++) {
            seg seg0(n);
            time_manager tm(n);
            for (int i = 0; i < n; i++) {
                seg0.set(i, S{i, i + 1, -1});
            }
            int now = 0;
            for (int q = 0; q < 3000; q++) {
                int ty = randint(0, 3);
                int l, r;
                std::tie(l, r) = randpair(0, n);
                if (ty == 0) {
                    auto res = seg0.prod(l, r);
                    ASSERT_EQ(l, res.l);
                    ASSERT_EQ(r, res.r);
                    ASSERT_EQ(tm.prod(l, r), res.time);
                } else if (ty == 1) {
                    auto res = seg0.get(l);
                    ASSERT_EQ(l, res.l);
                    ASSERT_EQ(l + 1, res.r);
                    ASSERT_EQ(tm.prod(l, l + 1), res.time);
                } else if (ty == 2) {
                    now++;
                    seg0.apply(l, r, T{now});
                    tm.action(l, r, now);
                } else if (ty == 3) {
                    now++;
                    seg0.apply(l, T{now});
                    tm.action(l, l + 1, now);
                } else {
                    assert(false);
                }
            }
        }
    }
}

TEST(LazySegtreeStressTest, MaxRightTest) {
    for (int n = 1; n <= 30; n++) {
        for (int ph = 0; ph < 10; ph++) {
            seg seg0(n);
            time_manager tm(n);
            for (int i = 0; i < n; i++) {
                seg0.set(i, S{i, i + 1, -1});
            }
            int now = 0;
            for (int q = 0; q < 1000; q++) {
                int ty = randint(0, 2);
                int l, r;
                std::tie(l, r) = randpair(0, n);
                if (ty == 0) {
                    ASSERT_EQ(r, seg0.max_right(l, [&](S s) {
                        if (s.l == -1) return true;
                        assert(s.l == l);
                        assert(s.time == tm.prod(l, s.r));
                        return s.r <= r;
                    }));
                } else {
                    now++;
                    seg0.apply(l, r, T{now});
                    tm.action(l, r, now);
                }
            }
        }
    }
}

TEST(LazySegtreeStressTest, MinLeftTest) {
    for (int n = 1; n <= 30; n++) {
        for (int ph = 0; ph < 10; ph++) {
            seg seg0(n);
            time_manager tm(n);
            for (int i = 0; i < n; i++) {
                seg0.set(i, S{i, i + 1, -1});
            }
            int now = 0;
            for (int q = 0; q < 1000; q++) {
                int ty = randint(0, 2);
                int l, r;
                std::tie(l, r) = randpair(0, n);
                if (ty == 0) {
                    ASSERT_EQ(l, seg0.min_left(r, [&](S s) {
                        if (s.l == -1) return true;
                        assert(s.r == r);
                        assert(s.time == tm.prod(s.l, r));
                        return l <= s.l;
                    }));
                } else {
                    now++;
                    seg0.apply(l, r, T{now});
                    tm.action(l, r, now);
                }
            }
        }
    }
}
