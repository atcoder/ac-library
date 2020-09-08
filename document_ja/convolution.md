# Convolution

畳み込みを行います。数列 $a_0, a_1, \cdots, a_{N - 1}$ と数列 $b_0, b_1, \cdots, b_{M - 1}$ から、長さ $N + M - 1$ の数列

$$c_i = \sum_{j = 0}^i a_j b_{i - j}$$

を計算します。

## convolution

```cpp
(1) vector<T> convolution<int m = 998244353>(vector<T> a, vector<T> b)
💻(2) vector<static_modint<m>> convolution<int m>(vector<static_modint<m>> a, vector<static_modint<m>> b)
```

畳み込みを $\bmod m$ で計算します。$a, b$ の少なくとも一方が空配列の場合は空配列を返します。

**@{keyword.constraints}**

- $2 \leq m \leq 2 \times 10^9$
- $\mathrm{m}$ は素数
- $2^c | (\mathrm{m} - 1)$ かつ $|a| + |b| - 1 \leq 2^c$ なる $c$ が存在する
- (1) `T`は`int, uint, ll, ull`

**@{keyword.complexity}**

$n = |a| + |b|$ として

- $O(n\log{n} + \log{\mathrm{mod}})$

## convolution_ll

```cpp
vector<ll> convolution_ll(vector<ll> a, vector<ll> b)
```

畳み込みを計算します。$a, b$ の少なくとも一方が空配列の場合は空配列を返します。

**@{keyword.constraints}**

- $|a| + |b| - 1 \leq 2^{24}$
- 畳み込んだ後の配列の要素が全て`ll`に収まる

**@{keyword.complexity}**

$n = |a| + |b|$ として

- $O(n\log{n})$

## @{keyword.examples}

@{example.convolution_int_practice}

@{example.convolution_practice}
