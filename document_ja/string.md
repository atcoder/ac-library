# String

文字列アルゴリズム詰め合わせです。
文字列に関する様々なアルゴリズムが入っています。

文字列 `s` の $a$ 番目から $b - 1$ 番目の要素のsubstringを、`s[a..b)`と表記します。

## suffix_array

```cpp
(1) vector<int> suffix_array(string s)
(2) vector<int> suffix_array<T>(vector<T> s)
(3) vector<int> suffix_array(vector<int> s, int upper)
```

長さ $n$ の文字列 `s` のSuffix Arrayとして、長さ $n$ の vector を返す。
Suffix Array `sa` は $(0, 1, \dots, n - 1)$ の順列であって、各 $i = 0,1, \cdots ,n-2$ について `s[sa[i]..n) < s[sa[i+1]..n)` を満たすもの。

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$
- (2) `T` は `int, uint, ll, ull`
- (3) $0 \leq \mathrm{upper} \leq 10^8$
- (3) $s$ のすべての要素 $x$ について $0 \leq x \leq \mathrm{upper}$

計算量

- (1) $O(n)$
- (2) 時間 $O(n \log n)$ 空間 $O(n)$
- (3) $O(n + \mathrm{upper})$

## lcp_array

```cpp
(1) vector<int> lcp_array(string s, vector<int> sa)
(2) vector<int> lcp_array<T>(vector<T> s, vector<int> sa)
```

長さ $n$ の文字列 `s` のLCP Arrayとして、長さ $n-1$ の配列を返す。$i$ 番目の要素は `s[sa[i]..n), s[sa[i+1]..n)` の LCP(Longest Common Prefix) の長さ。

**@{keyword.constraints}**

- `sa` は `s` のSuffix Array
- $1 \leq n \leq 10^8$
- (2): `T` は `int, uint, ll, ull`

**@{keyword.complexity}**

- $O(n)$

## z_algorithm

```cpp
(1) vector<int> z_algorithm(string s)
(2) vector<int> z_algorithm<T>(vector<T> s)
```

入力の長さを $n$ として、長さ $n$ の配列を返す。
$i$ 番目の要素は `s[0..n)`と`s[i..n)`のLCP(Longest Common Prefix)の長さ。

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$
- (2): `T` は `int, uint, ll, ull`

**@{keyword.complexity}**

- $O(n)$

## @{keyword.examples}

@{example.sa_usage}

@{example.sa_practice}
