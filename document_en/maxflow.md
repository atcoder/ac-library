# MaxFlow

It solves [maximum flow problem](https://en.wikipedia.org/wiki/Maximum_flow_problem).

## Constructor

```cpp
mf_graph<Cap> graph(int n)
```

It creates a graph of `n` vertices and $0$ edges. `Cap` is the type of the capacity.

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$
- `Cap` is `int` or `ll`

**@{keyword.complexity}**

- $O(n)$

## add_edge

```cpp
int graph.add_edge(int from, int to, Cap cap);
```

It adds an edge oriented from the vertex `from` to the vertex `to` with the capacity `cap` and the flow amount $0$. It returns an integer $k$ such that this is the $k$-th edge that is added.

**@{keyword.constraints}**

- $0 \leq \mathrm{from}, \mathrm{to} \lt n$
- $0 \leq \mathrm{cap}$

**@{keyword.complexity}**

- $O(1)$ amortized

## flow

```cpp
(1) Cap graph.flow(int s, int t);
(2) Cap graph.flow(int s, int t, Cap flow_limit);
```

- It augments the flow from $s$ to $t$ as much as possible. It returns the amount of the flow augmented.
- You may call it multiple times. See [Appendix](./appendix.html) for further details.

**@{keyword.constraints}**

- $s \neq t$
- The answer should be in `Cap`.

**@{keyword.complexity}**

- $O(\min(n^{\frac{2}{3}}m, m^{\frac{3}{2}}))$ (if all the capacities are $1$) or
- $O(n^2 m)$ (general),

where $m$ is the number of added edges.

## min_cut

```cpp
vector<bool> graph.min_cut(int s)
```

It returns a vector of length $n$, such that the $i$-th element is `true` if and only if there is a directed path from $s$ to $i$ in the residual network.
The returned vector corresponds to a $s-t$ minimum cut after calling `flow(s, t)` exactly once without `flow_limit`. See [Appendix](./appendix.html) for further details.

**@{keyword.complexity}**

- $O(n + m)$, where $m$ is the number of added edges.

## get_edge / edges

```cpp
struct mf_graph<Cap>::edge {
    int from, to;
    Cap cap, flow;
};

(1) mf_graph<Cap>::edge graph.get_edge(int i);
(2) vector<mf_graph<Cap>::edge> graph.edges();
```

- It returns the current internal state of the edges.
- The edges are ordered in the same order as added by `add_edge`.

**@{keyword.constraints}**

- (1): $0 \leq i \lt m$

**@{keyword.complexity}**

- (1): $O(1)$
- (2): $O(m)$, where $m$ is the number of added edges.

## change_edge

```cpp
void graph.change_edge(int i, Cap new_cap, Cap new_flow);
```

It changes the capacity and the flow amount of the $i$-th edge to `new_cap` and `new_flow`, respectively. It doesn't change the capacity or the flow amount of other edges. See [Appendix](./appendix.html) for further details.

**@{keyword.constraints}**

- $0 \leq \mathrm{newflow} \leq \mathrm{newcap}$

**@{keyword.complexity}**

- $O(1)$

## @{keyword.examples}

@{example.maxflow_practice}
