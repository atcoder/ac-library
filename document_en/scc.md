# SCC

It calculates the strongly connected components of directed graphs.

## Constructor

```cpp
scc_graph graph(int n)
```

It creates a directed graph with $n$ vertices and $0$ edges.

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$

**@{keyword.complexity}**

- $O(n)$

## add_edge

```cpp
void graph.add_edge(int from, int to)
```

It adds a directed edge from the vertex `from` to the vertex `to`.

**@{keyword.constraints}**

- $0 \leq \mathrm{from} \lt n$
- $0 \leq \mathrm{to} \lt n$

**@{keyword.complexity}**

- $O(1)$ amortized

## scc

```cpp
vector<vector<int>> graph.scc()
```

It returns the list of the "list of the vertices" that satisfies the following.

- Each vertex is in exactly one "list of the vertices".
- Each "list of the vertices" corresponds to the vertex set of a strongly connected component. The order of the vertices in the list is undefined.
- The list of "list of the vertices" are sorted in topological order, i.e., for two vertices $u, v$ in different strongly connected components, if there is a directed path from $u$ to $v$, the list containing $u$ appears earlier than the list containing $v$.

**@{keyword.complexity}**

- $O(n + m)$, where $m$ is the number of added edges.

## @{keyword.examples}

@{example.scc_practice}
