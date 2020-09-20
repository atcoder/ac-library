# Fenwick Tree

Given an array of length $N$, it processes the following queries in $O(\log N)$ time.

- Updating an element
- Calculating the sum of the elements of an interval

## Constructor

```cpp
fenwick_tree<T> fw(int n)
```

- It creates an array $a_0, a_1, \cdots, a_{n-1}$ of length $n$. All the elements are initialized to $0$.

**@{keyword.constraints}**

- `T` is `int`, `uint`, `ll`, `ull`, or `modint`
- $0 \leq n \leq 10^8$

**@{keyword.complexity}**

- $O(n)$

## add

```cpp
void fw.add(int p, T x)
```

It processes `a[p] += x`.

**@{keyword.constraints}**

- $0 \leq p < n$

**@{keyword.complexity}**

- $O(\log n)$

## sum

```cpp
T fw.sum(int l, int r)
```

It returns `a[l] + a[l + 1] + ... + a[r - 1]`.
If `T` is integer type(`int`, `uint`, `ll`, or `ull`), it returns the answer in $\bmod 2^{\mathrm{bit}}$, if overflowed.

**@{keyword.constraints}**

- $0 \leq l \leq r \leq n$

**@{keyword.complexity}**

- $O(\log n)$

## @{keyword.examples}

@{example.fenwick_practice}
