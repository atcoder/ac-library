# Modint

It is the struct that treats the modular arithmetic. All the remaining parts of AC Library works without modint, so you don't necessarily read this to use the remaining parts.

For most of the problems, it is sufficient to use `modint998244353`, `modint1000000007`, or `modint`, which can be used as follows.

```cpp
#include <atcoder/modint>
#include <iostream>

using namespace std;
using namespace atcoder;

using mint = modint998244353;
// or: typedef modint998244353 mint;

int main() {
    // print sum of array (mod 998244353)
    int n;
    cin >> n;
    mint sum = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sum += x;
    }
    cout << sum.val() << endl;
}
```

If the mod is not fixed, you can use `modint` as follows.

```cpp
#include <atcoder/modint>
#include <iostream>

using namespace std;

using mint = modint;
// or: typedef modint mint;

int main() {
    // print sum of array (input mod)
    int n, mod;
    cin >> n >> mod;
    mint::set_mod(mod);
    mint sum = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sum += x;
    }
    cout << sum.val() << endl;
}
```

All the functions except `set_mod` work for all three of them.

## Constructor

```cpp
(1) modint x()
(2) modint x<T>(T y)
```

- (1) It is the default constructor of modint. $0$ will be stored.
- (2) It is the constructor for the integer type `T`(`int, char, ull, bool, ...`). `y` is stored in modint after taking mod.

## set_mod

```cpp
void modint::set_mod(int m)
```

It sets the mod. It must be called first.

**@{keyword.constraints}**

- $1 \leq m \leq 2 \times 10^9 + 1000$

**@{keyword.complexity}**

- $O(1)$

## mod

```cpp
int modint::mod()
```

It returns the mod.

## val

```cpp
int x.val();
```

It returns the value that is stored in `x`.

## Operations

The following operations work.

```cpp
-modint;

modint++;
modint--;
++modint;
--modint;

modint + modint;
modint - modint;
modint * modint;
modint / modint;

modint += modint;
modint -= modint;
modint *= modint;
modint /= modint;

modint == modint;
modint != modint;
```

The following also works, because it is interpreted as `modint(1) + x`.

```cpp
modint x = 10;
1 + x;
```

The following also works, because it is interpreted as `y * modint(z)`.

```cpp
modint::set_mod(11);
modint y = 10;
int z = 1234;
y * z;
```

**@{keyword.constraints}**

- `gcd(b.val(), mod) == 1` should be satisfied when evaluating `a / b` (or `a /= b`).

**@{keyword.complexity}**

- $O(1)$ (all operations except division)
- $O(\log \mathrm{mod})$ (division)

## pow

```cpp
modint x.pow(ll n)
```

It returns $x^n$.

**@{keyword.constraints}**

- $0 \le n$

**@{keyword.complexity}**

- $O(\log n)$

## inv

```cpp
modint x.inv()
```

It returns $y$ with $xy \equiv 1$.

**@{keyword.constraints}**

- `gcd(x.val(), mod) = 1`

**@{keyword.complexity}**

- $O(\log \mathrm{mod})$

## raw

```cpp
modint modint::raw(int x)
```

It returns `modint(x)` without taking mod. It is the function for constant-factor speedup.

For example, the following code works even if `i` is greater than or equal to mod, because mod is automatically taken.

```cpp
modint a;
int i;
a += i;
```

However, in the following code, it is ensured that `i` is less than mod.

```cpp
int main() {
    modint::set_mod(1000000007);
    modint a = 1;
    for (int i = 1; i < 100000; i++) {
        a += i;
    }
}
```

In such a situation, we can decrease the number of mod operations as follows.

```cpp
int main() {
    modint::set_mod(1000000007);
    modint a = 1;
    for (int i = 1; i < 100000; i++) {
        a += modint::raw(i);
    }
}
```

When the value more than or equal to mod is assigned to `modint::raw(x)`, the behavior is undefined.

**@{keyword.constraints}**

- $0 \leq x \lt \mathrm{mod}$

## Tips (other mod)

You can use the other fixed mod like `1000000009` as follows.

```cpp
using mint = static_modint<1000000009>;
```

`modint998244353` (resp. `modint1000000007`) is the alias of `static_modint<998244353>` (resp. `static_modint<1000000007>`).

```cpp
using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
```

## Tips (multiple mods)

You can use multiple mods as follows.

```cpp
using mint0 = dynamic_modint<0>;
using mint1 = dynamic_modint<1>;
```

`modint` is the alias of `dynamic_modint<-1>`.

```cpp
using modint = dynamic_modint<-1>;
```

## @{keyword.examples}

@{example.modint_usage}
