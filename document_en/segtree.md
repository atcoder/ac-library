# Segtree

It is the data structure for [monoids](https://en.wikipedia.org/wiki/Monoid) $(S, \cdot: S \times S \to S, e \in S)$, i.e., the algebraic structure that satisfies the following properties.

- associativity: $(a \cdot b) \cdot c$ = $a \cdot (b \cdot c)$ for all $a, b, c \in S$
- existence of the identity element: $a \cdot e$ = $e \cdot a$ = $a$ for all $a \in S$

Given an array $S$ of length $N$, it processes the following queries in $O(\log N)$ time (see [Appendix](./appendix.html) for further details).

- Updating an element
- Calculating the product of the elements of an interval

For simplicity, in this document, we assume that the oracles `op` and `e` work in constant time. If these oracles work in $O(T)$ time, each time complexity appear in this document is multipled by $O(T)$.

## Constructor

```cpp
(1) segtree<S, op, e> seg(int n)
(2) segtree<S, op, e> seg(vector<S> v)
```

The following should be defined.

- The type `S`
- The binary operation `S op(S a, S b)`
- The identity element `S e()`

For example, for Range Minimum Query, the definitions are as follows.

```cpp
int op(int a, int b) {
    return min(a, b);
}

int e() {
    return (int)(1e9);
}

segtree<int, op, e> seg(10);
```

- (1): It creates an array `a` of length `n`. All the elements are initialized to `e()`.
- (2): It creates an array `a` of length `n = v.size()`, initialized to `v`.

See examples and [here](https://atcoder.jp/contests/practice2/editorial) for further details.

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$

**@{keyword.complexity}**

- $O(n)$

## set

```cpp
void seg.set(int p, S x)
```

It assigns $x$ to `a[p]`.

**@{keyword.constraints}**

- $0 \leq p < n$

**@{keyword.complexity}**

- $O(\log n)$

## get

```cpp
S seg.get(int p)
```

It returns `a[p]`.

**@{keyword.constraints}**

- $0 \leq p < n$

**@{keyword.complexity}**

- $O(1)$

## prod

```cpp
S seg.prod(int l, int r)
```

It returns `op(a[l], ..., a[r - 1])`, assuming the properties of the monoid. It returns `e()` if $l = r$.

**@{keyword.constraints}**

- $0 \leq l \leq r \leq n$

**@{keyword.complexity}**

- $O(\log n)$

## all_prod

```cpp
S seg.all_prod()
```

It returns `op(a[0], ..., a[n - 1])`, assuming the properties of the monoid. It returns `e()` if $n = 0$.

**@{keyword.complexity}**

- $O(1)$

## max_right

```cpp
(1) int seg.max_right<f>(int l)
(2) int seg.max_right<F>(int l, F f)
```

- (1): It applies binary search on the segment tree. The function `bool f(S x)` should be defined.  
- (2): The function object that takes `S` as the argument and returns `bool` should be defined.  

It returns an index `r` that satisfies both of the following.

- `r = l` or `f(op(a[l], a[l + 1], ..., a[r - 1])) = true`
- `r = n` or `f(op(a[l], a[l + 1], ..., a[r])) = false`

If `f` is monotone, this is the maximum `r` that satisfies `f(op(a[l], a[l + 1], ..., a[r - 1])) = true`.

**@{keyword.constraints}**

- if `f` is called with the same argument, it returns the same value, i.e., `f` has no side effect.
- `f(e()) = true`
- $0 \leq l \leq n$

**@{keyword.complexity}**

- $O(\log n)$

## min_left

```cpp
(1) int seg.min_left<f>(int r)
(2) int seg.min_left<F>(int r, F f)
```

- (1): It applies binary search on the segment tree. The function `bool f(S x)` should be defined.  
- (2): The function object that takes `S` as the argument and returns `bool` should be defined.  

It returns an index `l` that satisfies both of the following.

- `l = r` or `f(op(a[l], a[l + 1], ..., a[r - 1])) = true`
- `l = 0` or `f(op(a[l - 1], a[l], ..., a[r - 1])) = false`

If `f` is monotone, this is the minimum `l` that satisfies `f(op(a[l], a[l + 1], ..., a[r - 1])) = true`.

**@{keyword.constraints}**

- if `f` is called with the same argument, it returns the same value, i.e., `f` has no side effect.
- `f(e()) = true`
- $0 \leq r \leq n$

**@{keyword.complexity}**

- $O(\log n)$

## @{keyword.examples}

@{example.segtree_practice}
