# Appendix / FAQ

## 動作環境

- `ATCODER_`で始まる名前のマクロを使わないでください。
- 多くの環境で動くように作っていますが、C++標準からある程度の拡張機能を要求します。具体的には以下のことを仮定します。
  - `__int128 / unsigned __int128(g++, clang++)` か `_mul128 / _umul128(Visual Studio)` が使えること
  - `__builtin_(ctz/ctzll/clz/clzll/popcount)(g++, clang++)` か `_BitScan(Forward/Reverse)(Visual Studio)` が使えること
  - `char / short / int / ll`が `8 / 16 / 32 / 64` bit、またその`unsigned`型(および`signed char`)も同じbit長
  - 💻 [符号付き整数型が2の補数表現であることを規定](https://cpprefjp.github.io/lang/cpp20/signed_integers_are_twos_complement.html)

## インストール方法

### g++ / clang++へのインストール方法

一番わかりやすい方法は、トップページに書いたように、`main.cpp`と同じ場所に`atcoder`フォルダを置いて、`g++ main.cpp -std=c++14 -I .`と実行することです。ここで、`.`はフォルダを表す記号です(本当に I の後にスペース、点、と入力します。)

`atcoder`フォルダをいちいちコピーしたくない場合は以下のような方法があります。

- `g++ main.cpp -std=c++14 -I /path/to/ac-library`のように指定する (`/path/to/ac-library` は自分のPCの `ac-library` を置いてある場所へ書き換えてください)。
- 環境変数 `CPLUS_INCLUDE_PATH` で、`CPLUS_INCLUDE_PATH="/path/to/ac-library"`のように`atcoder`フォルダの場所を指定する。(Windowsの場合は、[ユーザー環境変数の設定画面](https://img.atcoder.jp/practice2/01333b7c5575b09b5868376ef242aa52.png) で、変数の欄に `CPLUS_INCLUDE_PATH` 値の欄に `C:\path\to\ac-library`　などと入力する。スラッシュではなくバックスラッシュを用いることに注意。なお、バックスラッシュは環境によっては円記号として表示されることがあります)。すると普通に`g++ main.cpp -std=c++14`とコンパイルできる。

### Visual Studioへのインストール方法

古いVisual Studioを使っている場合、アップデートしてください。Visual Studio 2017 / 2019をサポートしています。

Visual Studioがインストールされているならば、以下のようなフォルダがあるはずです。

- `C:\Program Files (x86)\Microsoft Visual Studio\2019\(Community, Professional or Enterprise)\VC\Tools\MSVC\(Some number, e.g. 14.27.29110)\include`
- `C:\Program Files (x86)\Microsoft Visual Studio\2017\(Community, Professional or Enterprise)\VC\Tools\MSVC\(Some number, e.g. 14.10.25017)\include`

このなかに丸ごと `atcoder` フォルダをコピーしてください。つまり、

- `C:\Program Files (x86)\Microsoft Visual Studio\2019\(Community, Professional or Enterprise)\VC\Tools\MSVC\(Some number, e.g. 14.27.29110)\include\atcoder\dsu.hpp`

となるように配置してください。

## 他のジャッジへの提出方法

`expander.py`というスクリプト(python3.5 or later)を用意しています。
`python3 expander.py main.cpp`と実行すると`combined.cpp`が生成され、これは他のオンラインジャッジに提出できる形になっています。

テストはしていますが、サポート保証外です。

## ドキュメントの表記法 / 明記されていないこと

### 💻マーク

C++初心者には難しいかもしれない機能を表すマークです。AC Libraryは、このマークの付いた箇所を無視してもアルゴリズム的に困らないように設計されています。modintなどが該当します。

### テンプレート関数

例えば`suffix_array(v)`は`vector<int>`, `vector<ll>`などを引数に取れるのですが、これらをまとめて`suffix_array<T>(vector<T> v)`と表記します。

例えば`vector<int>`に格納された整数列 $v$ の suffix array を求めたいとき、

```cpp
vector<int> sa = suffix_array(v);
// vector<int> sa = suffix_array<int>(v); ではないことに注意
```

と使います。

### デフォルトコンストラクタ

構造体、例えば`scc_graph` などは、サンプルのように

```cpp
#include <atcoder/scc>;
using namespace atcoder;

int main() {
    int n;
    scanf("%d", &n);
    scc_graph g(n); // n 頂点からなるグラフを生成
    return 0;
}
```

といった宣言方法だけでなく、次のように初期化なしで宣言することも出来ます。

```cpp
#include <atcoder/scc>;
using namespace atcoder;

scc_graph g;

int main() {
    return 0;
}
```

このように宣言したときの挙動（デフォルトコンストラクタ）は、

- $O(1)$
- 生成されたものへのメンバ変数のアクセス, メンバ関数の呼び出しの挙動は全て未定義

となります。また、構造体に後から代入することも出来ます。

```cpp
#include <atcoder/scc>;
using namespace atcoder;

scc_graph g;

int main() {
    g = scc_graph(10);
    return 0;
}
```

### 辺の型

最大流ライブラリなどでは、辺の型として `mf_graph<Cap>::edge` というのを使います。

例えば、`mf_graph<int>` の辺の型は `mf_graph<int>::edge` です。
`::` が見慣れないかもしれないですが、`mf_graph<int>::edge` という文字列を`int`や`string`のように扱えばよいです。例えば

```cpp
vector<mf_graph<int>::edge> v;
mf_graph<int>::edge e;
```

のようになります。

### デフォルトテンプレート引数

convolution のように、以下のような表記法を用いることがあります。

```cpp
vector<T> convolution<int m = 998244353>(vector<T> a, vector<T> b)
```

これは、二通りの使い方ができることを表します。

```cpp
vector<long long> c = convolution(a, b);
vector<long long> c = convolution<924844033>(a, b);
```

上段のように使った場合は、$m$ の値は自動的に $998244353$ となります。
下段のように使った場合は、$m$ の値は明示的に与えた値 (この場合は $924844033$) となります。

### 💻 explicit 指定子

`modint` 以外の構造体のコンストラクタには explicit が付いています。

## Segtree / LazySegtree の厳密な要件

Segtree / LazySegtree を使いたい状況において、扱う代数構造が無限集合である場合があります。たとえば、与えられた区間の $\mathrm{max}$ を求める、与えられた区間内の全ての要素に定数を足す、の二種類のクエリに対応する LazySegtree はよくありますが、このときたとえば $S = \mathrm{int}$ としてしまうと、$S$ は加法について閉じていない (overflow を起こす可能性がある) ため、厳密な意味でドキュメント本編の制約を満たしません。そこで、AC Library では以下のような場合正しく動くことを保証しています。

### Segtree

- $S$ はドキュメント本編の条件を満たすような代数構造である。
- $e \in S' \subseteq S$
- ライブラリに与える型や演算は、引数および演算結果が全て $S'$ に含まれる場合、正しく動く
- 任意の時点の、任意の連続な部分列 $a_l, a_{l+1}, \cdots, a_{r-1}$ について、積$a_l \cdot a_{l+1} \cdot \ldots \cdot a_{r-1}$ が $S'$ に含まれる。

### LazySegtree

- $(S, F)$ はドキュメント本編の条件を満たすような代数構造である。
- $e \in S' \subseteq S, \mathrm{id} \in F' \subseteq F$
- ライブラリに与える型や演算は、引数および演算結果が全て $S', F'$ に含まれる場合、正しく動く
- 任意の時点の、任意の連続な部分列 $a_l, a_{l+1}, \cdots, a_{r-1}$ について、積$a_l \cdot a_{l+1} \cdot \ldots \cdot a_{r-1}$ が $S'$ に含まれる。
- 任意の要素に対し、その要素に適用された関数を順に $f_0, f_1, ..., f_{k-1} \in F$ としたとき、任意の連続な部分列 $f_l, \cdots, f_{r-1}$ について、合成 $f_{r-1} \circ f_{l+1} \circ \dots \circ f_{l}$ が $F'$ に含まれる。

たとえば、最初の例で自然に $(S, F)$ を定めると以下のようになりますが、これは無限集合です。

- $S = \mathbb{Z} \cup \{-\infty\}$
- $S$ 上の二項演算 $\cdot$ は $\mathrm{max}$ ($e = -\infty$)
- $F$ は整数定数を加える写像全体の集合 ($\mathrm{id}$ は $0$ を加える写像)

$(S', F')$ を以下のように定めることで、制約が十分小さければこのライブラリで扱うことができます。

- $S' = (\mathbb{Z} \cap (-2^{31}, 2^{31})) \cup \{-\infty\}$
- $S’$ を表す型として $\mathrm{int}$ を選択し、$-\infty$ は $\mathrm{int}$ の元 $-2^{31}$ として、その他はそのまま表す
- $F'$ は区間 $[-2^{31}, 2^{31})$ 内の整数定数を加える写像全体の集合で、型 $\mathrm{int}$ を用いて自然な対応で表す

## maxflowの挙動

内部では各辺 $e$ について $2$ つの変数、流量 $f_e$ と容量 $c_e$ を管理しています。頂点 $v$ から出る辺の集合を $\mathrm{out}(v)$, 入る辺の集合を$\mathrm{in}(v)$ 、また頂点 $v$ について $g(v, f) = \sum_{e \in \mathrm{in}(v)}{f_e} - \sum_{e \in \mathrm{out}(v)}{f_e}$ とします。

### `flow(s, t)`

これを呼ぶと各辺の流量を変更します。厳密には変更前と変更後の流量を $f_e$, $f'_e$ として、以下の条件を満たすように変更します。

- $0 \leq f'_e \leq c_e$
- $s, t$ 以外の全ての頂点 $v$ について、$g(v, f) = g(v, f')$
- (flow_limitを指定した場合) $g(t, f') - g(t, f) \leq \mathrm{flow\\_limit}$
- $g(t, f') - g(t, f)$ が以上の条件を満たすうち最大。この $g(t, f') - g(t, f)$ を返す

### `min_cut(s)`

各辺 $e = (u, v, f_e, c_e)$について、$f_e \lt c_e$ ならば辺 $(u, v)$ を張り、$0 \lt f_e$ ならば辺 $(v, u)$ を張ったと仮定したとき、頂点 $s$ から到達可能な頂点の集合を返します。

### `change_edge(i, new_cap, new_flow)`

辺 $i$ の流量、容量のみを `new_flow`, `new_cap` へ変更します。
