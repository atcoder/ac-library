# DSU

Given an undirected graph, it processes the following queries in $O(\alpha(n))$ time (amortized).

- Edge addition
- Deciding whether given two vertices are in the same connected component

Each connected component internally has a representative vertex.

When two connected components are merged by edge addition, one of the two representatives of these connected components becomes the representative of the new connected component.

## Constructor

```cpp
dsu d(int n)
```

- It creates an undirected graph with $n$ vertices and $0$ edges.

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$

**@{keyword.complexity}**

- $O(n)$

## merge

```cpp
int d.merge(int a, int b)
```

It adds an edge $(a, b)$.

If the vertices $a$ and $b$ were in the same connected component, it returns the representative of this connected component. Otherwise, it returns the representative of the new connected component.

**@{keyword.constraints}**

- $0 \leq a < n$
- $0 \leq b < n$

**@{keyword.complexity}**

- $O(\alpha(n))$ amortized

## same

```cpp
bool d.same(int a, int b)
```

It returns whether the vertices $a$ and $b$ are in the same connected component.

**@{keyword.constraints}**

- $0 \leq a < n$
- $0 \leq b < n$

**@{keyword.complexity}**

- $O(\alpha(n))$ amortized

## leader

```cpp
int d.leader(int a)
```

It returns the representative of the connected component that contains the vertex $a$.

**@{keyword.constraints}**

- $0 \leq a < n$

**@{keyword.complexity}**

- $O(\alpha(n))$ amortized

## size

```cpp
int d.size(int a)
```

It returns the size of the connected component that contains the vertex $a$.

**@{keyword.constraints}**

- $0 \leq a < n$

**@{keyword.complexity}**

- $O(\alpha(n))$ amortized

## groups

```cpp
vector<vector<int>> d.groups()
```

It divides the graph into connected components and returns the list of them.

More precisely, it returns the list of the "list of the vertices in a connected component".
Both of the orders of the connected components and the vertices are undefined.

**@{keyword.complexity}**

- $O(n)$

## @{keyword.examples}

@{example.dsu_practice}
