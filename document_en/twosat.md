# 2-SAT

It solves 2-SAT.

For variables $x_0, x_1, \cdots, x_{N - 1}$ and clauses with form

- $(x_i = f) \lor (x_j = g)$,

it decides whether there is a truth assignment that satisfies all clauses.

## Constructor

```cpp
two_sat ts(int n)
```

It creates a 2-SAT of $n$ variables and $0$ clauses.

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$

**@{keyword.complexity}**

- $O(n)$

## add_clause

```cpp
void ts.add_clause(int i, bool f, int j, bool g)
```

It adds a clause $(x_i = f) \lor (x_j = g)$.

**@{keyword.constraints}**

- $0 \leq i \lt n$
- $0 \leq j \lt n$

**@{keyword.complexity}**

- $O(1)$ amortized

## satisfiable

```cpp
bool ts.satisfiable()
```

If there is a truth assignment that satisfies all clauses, it returns `true`. Otherwise, it returns `false`.

**@{keyword.constraints}**

- You may call it multiple times.

**@{keyword.complexity}**

- $O(n + m)$, where $m$ is the number of added clauses.

## answer

```cpp
vector<bool> ts.answer()
```

It returns a truth assignment that satisfies all clauses of the last call of `satisfiable`.
If we call it before calling `satisfiable` or when the last call of `satisfiable` returns `false`, it returns the vector of length $n$ with undefined elements.

**@{keyword.complexity}**

- $O(n)$

## @{keyword.examples}

@{example.twosat_practice}
