# SCC

有向グラフを強連結成分分解します。

## コンストラクタ

```cpp
scc_graph graph(int n)
```

$n$ 頂点 $0$ 辺の有向グラフを作る。

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$

**@{keyword.complexity}**

- $O(n)$

## add_edge

```cpp
void graph.add_edge(int from, int to)
```

頂点 `from` から頂点 `to` へ有向辺を足す。

**@{keyword.constraints}**

- $0 \leq \mathrm{from} \lt n$
- $0 \leq \mathrm{to} \lt n$

**@{keyword.complexity}**

- ならし $O(1)$

## scc

```cpp
vector<vector<int>> graph.scc()
```

以下の条件を満たすような、「頂点のリスト」のリストを返します。

- 全ての頂点がちょうど1つずつ、どれかのリストに含まれます。
- 内側のリストと強連結成分が一対一に対応します。リスト内での頂点の順序は未定義です。
- リストはトポロジカルソートされています。異なる強連結成分の頂点 $u, v$ について、$u$ から $v$ に到達できる時、$u$ の属するリストは $v$ の属するリストよりも前です。

**@{keyword.complexity}**

追加した辺の本数を $m$ として

- $O(n + m)$

## @{keyword.examples}

@{example.scc_practice}
