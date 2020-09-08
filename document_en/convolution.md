# Convolution

It calculates $(+,\times)$ convolution. Given two arrays $a_0, a_1, \cdots, a_{N - 1}$ and $b_0, b_1, \cdots, b_{M - 1}$, it calculates the array $c$ of length $N + M - 1$, defined by

$$c_i = \sum_{j = 0}^i a_j b_{i - j}$$

## convolution

```cpp
(1) vector<T> convolution<int m = 998244353>(vector<T> a, vector<T> b)
💻(2) vector<static_modint<m>> convolution<int m>(vector<static_modint<m>> a, vector<static_modint<m>> b)
```

It calculates the convolution in $\bmod m$. It returns an empty array if at least one of $a$ and $b$ are empty.

**@{keyword.constraints}**

- $2 \leq m \leq 2 \times 10^9$
- $m$ is prime.
- There is an integer $c$ with $2^c | (m - 1)$ and $|a| + |b| - 1 \leq 2^c$.
- (1) `T` is `int`, `uint`, `ll`, or `ull`.

**@{keyword.complexity}**

- $O(n\log{n} + \log{\mathrm{mod}})$, where $n = |a| + |b|$.

## convolution_ll

```cpp
vector<ll> convolution_ll(vector<ll> a, vector<ll> b)
```

It calculates the convolution. It returns an empty array if at least one of $a$ and $b$ are empty.

**@{keyword.constraints}**

- $|a| + |b| - 1 \leq 2^{24}$
- All the elements of the array are in `ll` after convolution

**@{keyword.complexity}**

- $O(n\log{n})$, where $n = |a| + |b|$.

## @{keyword.examples}

@{example.convolution_int_practice}

@{example.convolution_practice}
