# String

It contains string algorithms.

Let `s` be a string.
We denote the substring of `s` between $a$-th and $b - 1$-th character by `s[a..b)`.

## suffix_array

```cpp
(1) vector<int> suffix_array(string s)
(2) vector<int> suffix_array<T>(vector<T> s)
(3) vector<int> suffix_array(vector<int> s, int upper)
```

Given a string `s` of length $n$, it returns the suffix array of `s`.
Here, the suffix array `sa` of `s` is a permutation of $0, \cdots, n-1$ such that `s[sa[i]..n) < s[sa[i+1]..n)` holds for all $i = 0,1, \cdots ,n-2$.

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$
- (2) `T` is `int`, `uint`, `ll`, or `ull`.
- (3) $0 \leq \mathrm{upper} \leq 10^8$
- (3) $0 \leq x \leq \mathrm{upper}$ for all elements $x$ of $s$.

Complexity

- (1) $O(n)$-time
- (2) $O(n \log n)$-time, $O(n)$-space
- (3) $O(n + \mathrm{upper})$-time

## lcp_array

```cpp
(1) vector<int> lcp_array(string s, vector<int> sa)
(2) vector<int> lcp_array<T>(vector<T> s, vector<int> sa)
```

Given a string `s` of length $n$, it returns the LCP array of `s`.
Here, the LCP array of `s` is the array of length $n-1$, such that the $i$-th element is the length of the LCP (Longest Common Prefix) of `s[sa[i]..n)` and `s[sa[i+1]..n)`.

**@{keyword.constraints}**

- `sa` is the suffix array of `s`.
- $1 \leq n \leq 10^8$
- (2): `T` is `int`, `uint`, `ll`, or `ull`.

**@{keyword.complexity}**

- $O(n)$

## z_algorithm

```cpp
(1) vector<int> z_algorithm(string s)
(2) vector<int> z_algorithm<T>(vector<T> s)
```

Given a string of length $n$, it returns the array of length $n$, such that the $i$-th element is the length of the LCP (Longest Common Prefix) of `s[0..n)` and `s[i..n)`.

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$
- (2): `T` is `int`, `uint`, `ll`, or `ull`

**@{keyword.complexity}**

- $O(n)$

## @{keyword.examples}

@{example.sa_usage}

@{example.sa_practice}
