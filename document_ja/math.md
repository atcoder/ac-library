# Math

数論的アルゴリズム詰め合わせです。

## pow_mod

```cpp
ll pow_mod(ll x, ll n, int m)
```

$x^n \bmod m$ を返します。

**@{keyword.constraints}**

- $0 \le n$
- $1 \le m$

**@{keyword.complexity}**

- $O(\log n)$

## inv_mod

```cpp
ll inv_mod(ll x, ll m)
```

$xy \equiv 1 \pmod m$ なる $y$ のうち、$0 \le y < m$ を満たすものを返します。

**@{keyword.constraints}**

- $\gcd(x, m) = 1$
- $1 \leq m$

**@{keyword.complexity}**

- $O(\log m)$

## crt

```cpp
pair<ll, ll> crt(vector<ll> r, vector<ll> m)
```

同じ長さの配列 $r, m$ を渡します。この配列の長さを $n$ とした時、

$$x \equiv r[i] \pmod{m[i]}, \forall i \in \lbrace 0,1,\cdots, n - 1 \rbrace$$

を解きます。答えは(存在するならば) $y, z (0 \leq y < z = \mathrm{lcm}(m[i]))$ を用いて $x \equiv y \pmod z$ の形で書けることが知られており、この $(y, z)$ をpairとして返します。答えがない場合は $(0, 0)$ を返します。$n=0$ の時は $(0, 1)$ を返します。

**@{keyword.constraints}**

- $|r| = |m|$
- $1 \le m[i]$
- $\mathrm{lcm}(m[i])$ が `ll` に収まる。

**@{keyword.complexity}**

- $O(n \log{\mathrm{lcm}(m[i])})$

## floor_sum

```cpp
ll floor_sum(ll n, ll m, ll a, ll b)
```

$$\sum_{i = 0}^{n - 1} \left\lfloor \frac{a \times i + b}{m} \right\rfloor$$

を返します。答えがオーバーフローしたならば $\bmod 2^{\mathrm{64}}$ で等しい値を返します。

**@{keyword.constraints}**

- $0 \leq n \lt 2^{32}$
- $1 \leq m \lt 2^{32}$

**@{keyword.complexity}**

- $O(\log m)$

## @{keyword.examples}

@{example.floor_sum_practice}
