# Math

It contains number-theoretic algorithms.

## pow_mod

```cpp
ll pow_mod(ll x, ll n, int m)
```

It returns $x^n \bmod m$.

**@{keyword.constraints}**

- $0 \le n$
- $1 \le m$

**@{keyword.complexity}**

- $O(\log n)$

## inv_mod

```cpp
ll inv_mod(ll x, ll m)
```

It returns an integer $y$ such that $0 \le y < m$ and  $xy \equiv 1 \pmod m$.

**@{keyword.constraints}**

- $\gcd(x, m) = 1$
- $1 \leq m$

**@{keyword.complexity}**

- $O(\log m)$

## crt

```cpp
pair<ll, ll> crt(vector<ll> r, vector<ll> m)
```

Given two arrays $r,m$ with length $n$, it solves the modular equation system

$$x \equiv r[i] \pmod{m[i]}, \forall i \in \lbrace 0,1,\cdots, n - 1 \rbrace.$$

If there is no solution, it returns $(0, 0)$. Otherwise, all the solutions can be written as the form $x \equiv y \pmod z$, using integers
$y, z$ $(0 \leq y < z = \mathrm{lcm}(m[i]))$. It returns this $(y, z)$ as a pair. If $n=0$, it returns $(0, 1)$.

**@{keyword.constraints}**

- $|r| = |m|$
- $1 \le m[i]$
- $\mathrm{lcm}(m[i])$ is in `ll`.

**@{keyword.complexity}**

- $O(n \log{\mathrm{lcm}(m[i])})$

## floor_sum

```cpp
ll floor_sum(ll n, ll m, ll a, ll b)
```

It returns

$$\sum_{i = 0}^{n - 1} \left\lfloor \frac{a \times i + b}{m} \right\rfloor$$

It returns the answer in $\bmod 2^{\mathrm{64}}$, if overflowed.

**@{keyword.constraints}**

- $0 \leq n \lt 2^{32}$
- $1 \leq m \lt 2^{32}$

**@{keyword.complexity}**

- $O(\log m)$

## @{keyword.examples}

@{example.floor_sum_practice}
