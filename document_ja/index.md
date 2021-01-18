# AC(AtCoder) Library Document (@{keyword.tag})

@{keyword.info}

## インストール方法

- zipファイルを解凍すると、`ac-library`フォルダ, そしてその中に`atcoder`フォルダが入っているはずです。
- g++を使っている場合, `atcoder`フォルダを`main.cpp`と同じ場所に置いて、`g++ main.cpp -std=c++14 -I .`でコンパイルできます。  
  - `-std=c++14`か`-std=c++17`をつけてコンパイルする必要があります。
- 詳しくは [Appendix](./appendix.html) を参照してください。

## お約束

- 制約外の入力を入れたときの挙動はすべて未定義です。
- このドキュメントでは長い型を便宜上短く書きます
  - `unsigned int` → `uint`
  - `long long` → `ll`
  - `unsigned long long` → `ull`
- $0^0$ は $1$ です
- 明記されていない場合、多重辺や自己ループも入力可能です。

## リスト

`#include <atcoder/all>` : 一括include

### データ構造

- [`#include <atcoder/fenwicktree>`](./fenwicktree.html)
- [`#include <atcoder/segtree>`](./segtree.html)
- [`#include <atcoder/lazysegtree>`](./lazysegtree.html)
- [`#include <atcoder/string>`](./string.html)

### 数学

- [`#include <atcoder/math>`](./math.html)
- [`#include <atcoder/convolution>`](./convolution.html)
- 💻[`#include <atcoder/modint>`](./modint.html)

### グラフ

- [`#include <atcoder/dsu>`](./dsu.html)
- [`#include <atcoder/maxflow>`](./maxflow.html)
- [`#include <atcoder/mincostflow>`](./mincostflow.html)
- [`#include <atcoder/scc>`](./scc.html)
- [`#include <atcoder/twosat>`](./twosat.html)

## 付録

- [Appendix / FAQ](./appendix.html)

## テスト

- [こちら](https://atcoder.jp/contests/practice2) で実際にこの Library を使う問題を解いてみることができます。

## ライセンス

ヘッダファイル群(同梱の `atcoder` フォルダ以下)はCC0ライセンスで公開しています。詳しくは`atcoder/LICENSE`を参照してください。
