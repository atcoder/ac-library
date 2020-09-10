# Segtree

[モノイド](https://ja.wikipedia.org/wiki/%E3%83%A2%E3%83%8E%E3%82%A4%E3%83%89) $(S, \cdot: S \times S \to S, e \in S)$、つまり

- 結合律: $(a \cdot b) \cdot c$ = $a \cdot (b \cdot c)$ for all $a, b, c \in S$
- 単位元の存在: $a \cdot e$ = $e \cdot a$ = $a$ for all $a \in S$

を満たす代数構造に対し使用できるデータ構造です。

長さ $N$ の $S$ の配列に対し、

- 要素の $1$ 点変更
- 区間の要素の総積の取得

を $O(\log N)$ で行うことが出来ます。詳細な要件は [Appendix](./appendix.html) を参照してください。

また、このライブラリはオラクルとして`op, e`の2種類を使用しますが、これらが定数時間で動くものと仮定したときの計算量を記述します。オラクル内部の計算量が $O(f(n))$ である場合はすべての計算量が $O(f(n))$ 倍となります。

## コンストラクタ

```cpp
(1) segtree<S, op, e> seg(int n)
(2) segtree<S, op, e> seg(vector<S> v)
```

- 型 `S`
- 二項演算 `S op(S a, S b)`
- 単位元 `S e()`

を定義する必要があります。例として、Range Min Queryならば

```cpp
int op(int a, int b) {
    return min(a, b);
}

int e() {
    return (int)(1e9);
}

segtree<int, op, e> seg(10);
```

のようになります。

- (1): 長さ `n` の数列 `a` を作ります。初期値は全部`e()`です。
- (2): 長さ `n = v.size()` の数列 `a` を作ります。`v` の内容が初期値となります。

詳しくは、使用例や [こちら](https://atcoder.jp/contests/practice2/editorial) も参照してください。

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$

**@{keyword.complexity}**

- $O(n)$

## set

```cpp
void seg.set(int p, S x)
```

`a[p]` に `x` を代入します。

**@{keyword.constraints}**

- $0 \leq p < n$

**@{keyword.complexity}**

- $O(\log n)$

## get

```cpp
S seg.get(int p)
```

`a[p]` を返します。

**@{keyword.constraints}**

- $0 \leq p < n$

**@{keyword.complexity}**

- $O(1)$

## prod

```cpp
S seg.prod(int l, int r)
```

`op(a[l], ..., a[r - 1])` を、モノイドの性質を満たしていると仮定して計算します。$l = r$ のときは `e()` を返します。

**@{keyword.constraints}**

- $0 \leq l \leq r \leq n$

**@{keyword.complexity}**

- $O(\log n)$

## all_prod

```cpp
S seg.all_prod()
```

`op(a[0], ..., a[n - 1])` を計算します。$n = 0$ のときは `e()` を返します。

**@{keyword.complexity}**

- $O(1)$

## max_right

```cpp
(1) int seg.max_right<f>(int l)
(2💻) int seg.max_right<F>(int l, F f)
```

- (1): 関数 `bool f(S x)` を定義する必要があります。segtreeの上で二分探索をします。  
- (2): `S`を引数にとり`bool`を返す関数オブジェクトを渡して使用します。  

以下の条件を両方満たす `r` を(いずれか一つ)返します。

- `r = l` もしくは `f(op(a[l], a[l + 1], ..., a[r - 1])) = true`
- `r = n` もしくは `f(op(a[l], a[l + 1], ..., a[r])) = false`

`f`が単調だとすれば、`f(op(a[l], a[l + 1], ..., a[r - 1])) = true` となる最大の `r`、と解釈することが可能です。

**@{keyword.constraints}**

- `f`を同じ引数で呼んだ時、返り値は等しい(=副作用はない)
- `f(e()) = true`
- $0 \leq l \leq n$

**@{keyword.complexity}**

- $O(\log n)$

## min_left

```cpp
(1) int seg.min_left<f>(int r)
(2💻) int seg.min_left<F>(int r, F f)
```

- (1): 関数 `bool f(S x)` を定義する必要があります。segtreeの上で二分探索をします。  
- (2): `S`を引数にとり`bool`を返す関数オブジェクトを渡して使用します。  

以下の条件を両方満たす `l` を(いずれか一つ)返します。

- `l = r` もしくは `f(op(a[l], a[l + 1], ..., a[r - 1])) = true`
- `l = 0` もしくは `f(op(a[l - 1], a[l], ..., a[r - 1])) = false`

`f`が単調だとすれば、`f(op(a[l], a[l + 1], ..., a[r - 1])) = true` となる最小の `l`、と解釈することが可能です。

**@{keyword.constraints}**

- `f`を同じ引数で呼んだ時、返り値は等しい(=副作用はない)
- `f(e()) = true`
- $0 \leq r \leq n$

**@{keyword.complexity}**

- $O(\log n)$

## @{keyword.examples}

@{example.segtree_practice}
