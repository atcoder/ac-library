# MaxFlow

[最大フロー問題](https://ja.wikipedia.org/wiki/%E6%9C%80%E5%A4%A7%E3%83%95%E3%83%AD%E3%83%BC%E5%95%8F%E9%A1%8C) を解くライブラリです。

## コンストラクタ

```cpp
mf_graph<Cap> graph(int n)
```

`n` 頂点 $0$ 辺のグラフを作る。`Cap`は容量の型。

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$
- `Cap` は `int`, `ll`

**@{keyword.complexity}**

- $O(n)$

## add_edge

```cpp
int graph.add_edge(int from, int to, Cap cap);
```

`from`から`to`へ最大容量`cap`、流量 $0$ の辺を追加し、何番目に追加された辺かを返す。

**@{keyword.constraints}**

- $0 \leq \mathrm{from}, \mathrm{to} \lt n$
- $0 \leq \mathrm{cap}$

**@{keyword.complexity}**

- ならし $O(1)$

## flow

```cpp
(1) Cap graph.flow(int s, int t);
(2) Cap graph.flow(int s, int t, Cap flow_limit);
```

- (1) 頂点 $s$ から $t$ へ流せる限り流し、流せた量を返す。
- (2) 頂点 $s$ から $t$ へ流量 `flow_limit` に達するまで流せる限り流し、流せた量を返す。
- 複数回呼ぶことも可能で、その時の挙動は [Appendix](./appendix.html) を参照してください。

**@{keyword.constraints}**

- $s \neq t$
- $0 \leq s, t \lt n$
- 返り値が `Cap` に収まる

**@{keyword.complexity}**

$m$ を追加された辺数として

- $O((n + m) \sqrt{m})$ (辺の容量がすべて $1$ の時)
- $O(n^2 m)$
- 返り値を $F$ として $O(F(n + m))$

## min_cut

```cpp
vector<bool> graph.min_cut(int s)
```

長さ $n$ のvectorを返す。$i$ 番目の要素には、頂点 $s$ から $i$ へ残余グラフで到達可能なとき、またその時のみ `true` を返す。`flow(s, t)`をflow_limitなしでちょうど一回呼んだ後に呼ぶと、返り値は $s$, $t$ 間のmincutに対応します。詳細な挙動は [Appendix](./appendix.html) を参照してください。

**@{keyword.complexity}**

$m$ を追加された辺数として

- $O(n + m)$

## get_edge / edges

```cpp
struct mf_graph<Cap>::edge {
    int from, to;
    Cap cap, flow;
};

(1) mf_graph<Cap>::edge graph.get_edge(int i);
(2) vector<mf_graph<Cap>::edge> graph.edges();
```

- 今の内部の辺の状態を返す
- 辺の順番はadd_edgeで追加された順番と同一

**@{keyword.constraints}**

- (1): $0 \leq i \lt m$

**@{keyword.complexity}**

$m$ を追加された辺数として

- (1): $O(1)$
- (2): $O(m)$

## change_edge

```cpp
void graph.change_edge(int i, Cap new_cap, Cap new_flow);
```

$i$ 番目に追加された辺の容量、流量を`new_cap`, `new_flow`に変更する。他の辺の容量、流量は変更しない。詳細は [Appendix](./appendix.html) を参照してください

**@{keyword.constraints}**

- $0 \leq \mathrm{newflow} \leq \mathrm{newcap}$

**@{keyword.complexity}**

- $O(1)$

## @{keyword.examples}

@{example.maxflow_practice}
