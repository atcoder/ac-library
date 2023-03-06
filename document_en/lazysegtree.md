# Lazy Segtree

It is the data structure for the pair of a [monoid](https://en.wikipedia.org/wiki/Monoid) $(S, \cdot: S \times S \to S, e \in S)$ and a set $F$ of $S \to S$ mappings that satisfies the following properties.

- $F$ contains the identity map $\mathrm{id}$, where the identity map is the map that satisfies $\mathrm{id}(x) = x$ for all $x \in S$.
- $F$ is closed under composition, i.e., $f \circ g \in F$ holds for all $f, g \in F$.
- $f(x \cdot y) = f(x) \cdot f(y)$ holds for all $f \in F$ and $x, y \in S$.

Given an array $S$ of length $N$, it processes the following queries in $O(\log N)$ time (see [Appendix](./appendix.html) for further details).

- Acting the map $f\in F$ (cf. $x = f(x)$) on all the elements of an interval
- Calculating the product of the elements of an interval

For simplicity, in this document, we assume that the oracles `op`, `e`, `mapping`, `composition`, and `id` work in constant time. If these oracles work in $O(T)$ time, each time complexity appear in this document is multipled by $O(T)$.

## Constructor

```cpp
(1) lazy_segtree<S, op, e, F, mapping, composition, id> seg(int n);
(2) lazy_segtree<S, op, e, F, mapping, composition, id> seg(vector<S> v);
```

The following should be defined.

- The type `S` of the monoid
- The binary operation `S op(S a, S b)`
- The function `S e()` that returns $e$
- The type `F` of the map
- The function `S mapping(F f, S x)` that returns $f(x)$
- The function `F composition(F f, F g)` that returns $f \circ g$
- The function `F id()` that returns $\mathrm{id}$

See examples and [here](https://atcoder.jp/contests/practice2/editorial) for further details.

- (1): It creates an array `a` of length `n`. All the elements are initialized to `e()`.
- (2): It creates an array `a` of length `n = v.size()`, initialized to `v`.

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$

**@{keyword.complexity}**

- $O(n)$

## set

```cpp
void seg.set(int p, S x)
```

`a[p] = x`

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

- $O(\log n)$

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

## apply

```cpp
(1) void seg.apply(int p, F f)
(2) void seg.apply(int l, int r, F f)
```

- (1) It applies `a[p] = f(a[p])`.
- (2) It applies `a[i] = f(a[i])` for all `i = l..r-1`.

**@{keyword.constraints}**

- (1) $0 \leq p < n$
- (2) $0 \leq l \leq r \leq n$

**@{keyword.complexity}**

- $O(\log n)$

## max_right

```cpp
(1) int seg.max_right<g>(int l)
(2 ) int seg.max_right<G>(int l, G g)
```

- (1): It applies a binary search on the segment tree. The function `bool g(S x)` should be defined.  
- (2): The function object that takes `S` as the argument and returns `bool` should be defined.  

It returns an index `r` that satisfies both of the followings.

- `r = l` or `g(op(a[l], a[l + 1], ..., a[r - 1])) = true`
- `r = n` or `g(op(a[l], a[l + 1], ..., a[r])) = false`

If `g` is monotone, this is the maximum `r` that satisfies `g(op(a[l], a[l + 1], ..., a[r - 1])) = true`.

**@{keyword.constraints}**

- if `g` is called with the same argument, it returns the same value, i.e., `g` has no side effect.
- `g(e()) = true`
- $0 \leq l \leq n$

**@{keyword.complexity}**

- $O(\log n)$

## min_left

```cpp
(1) int seg.min_left<g>(int r)
(2 ) int seg.min_left<G>(int r, G g)
```

- (1): It applies a binary search on the segment tree. The function `bool g(S x)` should be defined.  
- (2): The function object that takes `S` as the argument and returns `bool` should be defined.  

It returns an index `l` that satisfies both of the following.

- `l = r` or `g(op(a[l], a[l + 1], ..., a[r - 1])) = true`
- `l = 0` or `g(op(a[l - 1], a[l], ..., a[r - 1])) = false`

If `g` is monotone, this is the minimum `l` that satisfies `g(op(a[l], a[l + 1], ..., a[r - 1])) = true`.

**@{keyword.constraints}**

- if `g` is called with the same argument, it returns the same value, i.e., `g` has no side effect.
- `g(e()) = true`
- $0 \leq r \leq n$

**@{keyword.complexity}**

- $O(\log n)$

## @{keyword.examples}

@{example.lazyseg_practice1}

@{example.lazyseg_practice2}
