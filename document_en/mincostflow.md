# MinCostFlow

It solves [Minimum-cost flow problem](https://en.wikipedia.org/wiki/Minimum-cost_flow_problem).

## Constructor

```cpp
mcf_graph<Cap, Cost> graph(int n);
```

It creates a directed graph with $n$ vertices and $0$ edges. `Cap` and `Cost` are the type of the capacity and the cost, respectively.

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$
- `Cap` and `Cost` are `int` or `ll`.

**@{keyword.complexity}**

- $O(n)$

## add_edge

```cpp
int graph.add_edge(int from, int to, Cap cap, Cost cost);
```

It adds an edge oriented from `from` to `to` with capacity `cap` and cost `cost`. It returns an integer $k$ such that this is the $k$-th edge that is added.

**@{keyword.constraints}**

- $0 \leq \mathrm{from}, \mathrm{to} \lt n$
- $0 \leq \mathrm{cap}, \mathrm{cost}$

**@{keyword.complexity}**

- $O(1)$ amortized

## min_cost_max_flow

```cpp
(1) pair<Cap, Cost> graph.flow(int s, int t);
(2) pair<Cap, Cost> graph.flow(int s, int t, Cap flow_limit);
```

- It augments the flow from $s$ to $t$ as much as possible. It returns the amount of the flow and the cost.
- (1) It augments the $s-t$ flow as much as possible.
- (2) It augments the $s-t$ flow as much as possible, until reaching the amount of `flow_limit`.

**@{keyword.constraints}**

- same as `min_cost_slope`.

**@{keyword.complexity}**

- same as `min_cost_slope`.

## min_cost_slope

```cpp
vector<pair<Cap, Cost>> graph.slope(int s, int t);
vector<pair<Cap, Cost>> graph.slope(int s, int t, Cap flow_limit);
```

Let $g$ be a function such that $g(x)$ is the cost of the minimum cost $s-t$ flow when the amount of the flow is exactly $x$. $g$ is known to be piecewise linear.
It returns $g$ as the list of the changepoints, that satisfies the followings.

- The first element of the list is $(0, 0)$.
- Both of `.first` and `.second` are strictly increasing.
- No three changepoints are on the same line.
- (1) The last element of the list is $(x, g(x))$, where $x$ is the maximum amount of the $s-t$ flow.
- (2) The last element of the list is $(y, g(y))$, where $y = \min(x, \mathrm{flow\\_limit})$.

**@{keyword.constraints}**

Let $x$ be the maximum cost among all edges.

- $s \neq t$
- $0 \leq s, t \lt n$
- You can't call `min_cost_slope` or `min_cost_max_flow` multiple times.
- The total amount of the flow is in `Cap`.
- The total cost of the flow is in `Cost`.
- (Cost : `int`): $0 \leq nx \leq 2 \times 10^9 + 1000$
- (Cost : `ll`): $0 \leq nx \leq 8 \times 10^{18} + 1000$

**@{keyword.complexity}**

- $O(F (n + m) \log (n + m))$, where $F$ is the amount of the flow and $m$ is the number of added edges.

## edges

```cpp
struct edge<Cap, Cost> {
    int from, to;
    Cap cap, flow;
    Cost cost;
};

(1) mcf_graph<Cap, Cost>::edge graph.get_edge(int i);
(2) vector<mcf_graph<Cap, Cost>::edge> graph.edges();
```

- It returns the current internal state of the edges.
- The edges are ordered in the same order as added by `add_edge`.

**@{keyword.constraints}**

- (1): $0 \leq i \lt m$

**@{keyword.complexity}**

- (1): $O(1)$
- (2): $O(m)$, where $m$ is the number of added edges.

## @{keyword.examples}

@{example.mincostflow_practice}
