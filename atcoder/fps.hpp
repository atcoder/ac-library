#ifndef ATCODER_FPS_HPP
#define ATCODER_FPS_HPP 1

#include <atcoder/convolution>
#include <atcoder/modint>

namespace atcoder {

using namespace std;

// https://opt-cp.com/fps-fast-algorithms
template<class T>
struct FormalPowerSeries : vector<T> {
    using vector<T>::vector;
    using vector<T>::operator=;
    using F = FormalPowerSeries;

    F operator-() const {
        F res(*this);
        for (auto &e : res) e = -e;
        return res;
    }
    F &operator*=(const T &g) {
        for (auto &e : *this) e *= g;
        return *this;
    }
    F &operator/=(const T &g) {
        assert(g != T(0));
        *this *= g.inv();
        return *this;
    }
    F &operator+=(const F &g) {
        int n = (int)this->size(), m = (int)g.size();
        for (int i = 0; i < min(n, m); i++) (*this)[i] += g[i];
        return *this;
    }
    F &operator-=(const F &g) {
        int n = (int)this->size(), m = (int)g.size();
        for (int i = 0; i < min(n, m); i++) (*this)[i] -= g[i];
        return *this;
    }
    F &operator<<=(const int d) {
        int n = (int)this->size();
        if (d >= n) *this = F(n);
        this->insert(this->begin(), d, 0);
        this->resize(n);
        return *this;
    }
    F &operator>>=(const int d) {
        int n = (int)this->size();
        this->erase(this->begin(), this->begin() + min(n, d));
        this->resize(n);
        return *this;
    }

    // O(n log n)
    F inv(int d = -1) const {
        int n = (int)this->size();
        assert(n != 0 && (*this)[0] != 0);
        if (d == -1) d = n;
        assert(d >= 0);
        F res{(*this)[0].inv()};
        for (int m = 1; m < d; m *= 2) {
            F f(this->begin(), this->begin() + min(n, 2*m));
            F g(res);
            f.resize(2*m), internal::butterfly(f);
            g.resize(2*m), internal::butterfly(g);
            for (int i = 0; i < 2 * m; i++) f[i] *= g[i];
            internal::butterfly_inv(f);
            f.erase(f.begin(), f.begin() + m);
            f.resize(2*m), internal::butterfly(f);
            for (int i = 0; i < 2 * m; i++) f[i] *= g[i];
            internal::butterfly_inv(f);
            T iz = T(2*m).inv(); iz *= -iz;
            for (int i = 0; i < m; i++) f[i] *= iz;
            res.insert(res.end(), f.begin(), f.begin() + m);
        }
        res.resize(d);
        return res;
    }

    // fast: FMT-friendly modulus only
    // O(n log n)
    F &multiply_inplace(const F &g, int d = -1) {
        int n = (int)this->size();
        if (d == -1) d = n;
        assert(d >= 0);
        *this = convolution(move(*this), g);
        this->resize(d);
        return *this;
    }
    F multiply(const F &g, const int d = -1) const { return F(*this).multiply_inplace(g, d); }
    // O(n log n)
    F &divide_inplace(const F &g, int d = -1) {
        int n = (int)this->size();
        if (d == -1) d = n;
        assert(d >= 0);
        *this = convolution(move(*this), g.inv(d));
        this->resize(d);
        return *this;
    }
    F divide(const F &g, const int d = -1) const { return F(*this).divide_inplace(g, d); }

    // O(n)
    F &integ_inplace() {
        int n = (int)this->size();
        assert(n > 0);
        if (n == 1) return *this = F{0};
        this->insert(this->begin(), 0);
        this->pop_back();
        vector<T> inv(n);
        inv[1] = 1;
        int p = T::mod();
        for (int i = 2; i < n; ++i) inv[i] = - inv[p%i] * (p/i);
        for (int i = 2; i < n; ++i) (*this)[i] *= inv[i];
        return *this;
    }
    F integ() const { return F(*this).integ_inplace(); }

    // O(n)
    F &deriv_inplace() {
        int n = (int)this->size();
        assert(n > 0);
        for (int i = 2; i < n; ++i) (*this)[i] *= i;
        this->erase(this->begin());
        this->push_back(0);
        return *this;
    }
    F deriv() const { return F(*this).deriv_inplace(); }

    // O(n log n)
    F &log_inplace(int d = -1) {
        int n = (int)this->size();
        assert(n > 0 && (*this)[0] == 1);
        if (d == -1) d = n;
        assert(d >= 0);
        if (d < n) this->resize(d);
        F f_inv = this->inv();
        this->deriv_inplace();
        this->multiply_inplace(f_inv);
        this->integ_inplace();
        return *this;
    }
    F log(const int d = -1) const { return F(*this).log_inplace(d); }

    // O(n log n)
    // https://arxiv.org/abs/1301.5804 (Figure 1, right)
    F &exp_inplace(int d = -1) {
        int n = (int)this->size();
        assert(n > 0 && (*this)[0] == 0);
        if (d == -1) d = n;
        assert(d >= 0);
        F g{1}, g_fft;
        this->resize(d);
        (*this)[0] = 1;
        F h_drv(this->deriv());
        for (int m = 1; m < d; m *= 2) {
            // prepare
            F f_fft(this->begin(), this->begin() + m);
            f_fft.resize(2*m), internal::butterfly(f_fft);

            // Step 2.a'
            if (m > 1) {
                F _f(m);
                for (int i = 0; i < m; i++) _f[i] = f_fft[i] * g_fft[i];
                internal::butterfly_inv(_f);
                _f.erase(_f.begin(), _f.begin() + m/2);
                _f.resize(m), internal::butterfly(_f);
                for (int i = 0; i < m; i++) _f[i] *= g_fft[i];
                internal::butterfly_inv(_f);
                _f.resize(m/2);
                _f /= T(-m) * m;
                g.insert(g.end(), _f.begin(), _f.begin() + m/2);
            }

            // Step 2.b'--d'
            F t(this->begin(), this->begin() + m);
            t.deriv_inplace();
            {
                // Step 2.b'
                F r{h_drv.begin(), h_drv.begin() + m-1};
                // Step 2.c'
                r.resize(m); internal::butterfly(r);
                for (int i = 0; i < m; i++) r[i] *= f_fft[i];
                internal::butterfly_inv(r);
                r /= -m;
                // Step 2.d'
                t += r;
                t.insert(t.begin(), t.back()); t.pop_back();
            }

            // Step 2.e'
            if (2*m < d || m == 1) {
                t.resize(2*m); internal::butterfly(t);
                g_fft = g; g_fft.resize(2*m); internal::butterfly(g_fft);
                for (int i = 0; i < 2 * m; i++) t[i] *= g_fft[i];
                internal::butterfly_inv(t);
                t.resize(m);
                t /= 2*m;
            }
            else { // This division of cases will only speed things up by a few percent.
                F g1(g.begin() + m/2, g.end());
                F s1(t.begin() + m/2, t.end());
                t.resize(m/2);
                g1.resize(m), internal::butterfly(g1);
                t.resize(m),  internal::butterfly(t);
                s1.resize(m), internal::butterfly(s1);
                for (int i = 0; i < m; i++) s1[i] = g_fft[i] * s1[i] + g1[i] * t[i];
                for (int i = 0; i < m; i++) t[i] *= g_fft[i];
                internal::butterfly_inv(t);
                internal::butterfly_inv(s1);
                for (int i = 0; i < m / 2; i++) t[i+m/2] += s1[i];
                t /= m;
            }

            // Step 2.f'
            F v(this->begin() + m, this->begin() + min<int>(d, 2*m)); v.resize(m);
            t.insert(t.begin(), m-1, 0); t.push_back(0);
            t.integ_inplace();
            for (int i = 0; i < m; i++) v[i] -= t[m+i];

            // Step 2.g'
            v.resize(2*m); internal::butterfly(v);
            for (int i = 0; i < 2 * m; i++) v[i] *= f_fft[i];
            internal::butterfly_inv(v);
            v.resize(m);
            v /= 2*m;

            // Step 2.h'
            for (int i = 0; i < min(d - m, m); i++) (*this)[m+i] = v[i];
        }
        return *this;
    }
    F exp(const int d = -1) const { return F(*this).exp_inplace(d); }

    // O(n log n)
    F &pow_inplace(long long k, int d = -1) {
        int n = (int)this->size();
        if (d == -1) d = n;
        assert(d >= 0);
        int l = 0;
        while ((*this)[l] == 0) ++l;
        if (l > d/k) return *this = F(d);
        T ic = (*this)[l].inv();
        T pc = (*this)[l].pow(k);
        this->erase(this->begin(), this->begin() + l);
        *this *= ic;
        this->log_inplace();
        *this *= k;
        this->exp_inplace();
        *this *= pc;
        this->insert(this->begin(), l*k, 0);
        this->resize(d);
        return *this;
    }
    F pow(const long long k, const int d = -1) const { return F(*this).pow_inplace(k, d); }

    F operator*(const T &g) const { return F(*this) *= g; }
    F operator/(const T &g) const { return F(*this) /= g; }
    F operator+(const F &g) const { return F(*this) += g; }
    F operator-(const F &g) const { return F(*this) -= g; }
    F operator<<(const int d) const { return F(*this) <<= d; }
    F operator>>(const int d) const { return F(*this) >>= d; }
};

using fps = FormalPowerSeries<modint998244353>;

}  // namespace atcoder

#endif  // ATCODER_FPS_HPP
