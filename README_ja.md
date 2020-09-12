注：これは [README.md](README.md) の日本語翻訳です。もし英語版と内容が一致しない場合、英語版の内容が優先されます。

# AC(AtCoder) Library

AC Library は [AtCoder](https://atcoder.jp/home) の公式ライブラリです。このリポジトリでは AC Library のコンテンツを管理しています。

以下のリンクを参考にしていただければと思います: 

- [AtCoder でのお知らせ](https://atcoder.jp/posts/518)
- [Codeforces でのお知らせ](https://codeforces.com/blog/entry/82400)
- [Practice Contest](https://atcoder.jp/contests/practice2)
- [AC Library Document(英語)](https://atcoder.github.io/ac-library/document_en/)
- [AC Library Document(日本語)](https://atcoder.github.io/ac-library/document_ja/)

## ポリシー

このプロジェクトの目標は以下の通りです

- **全ての AtCoder ユーザー** が、**最小限の PC の勉強努力** によって利用可能
- **競技プログラミングでの使用の利便性** を最大化。他の用途は完全に無視
- バグの無いライブラリ。理想の話ですが、これを追求

この方針により、C++の一部のマナーを意図的に無視しています。例えば、以下のようなものです。

- `size_t` を使わずに `int` を使用
- Segtree は関数オブジェクトではなく関数ポインタを使用
- …などなど

## 本プロジェクトの方向性

賛否両論あるので、このライブラリのコンテンツを増やすべきかどうかは決めていません。
このトピックに興味がある方は、[Codeforces での告知(英語)](https://codeforces.com/blog/entry/82400)で議論に参加してください。  
  
今のところ新機能の追加は予定しておらず、このリポジトリは

- Issues の解決
- 変更の記録
- Releases のバージョン管理

のみを行っています。

## Contributing

我々は **AtCoder ユーザーからのみ** issues/PRs を受け付けています。

誤字脱字などのミスや、もっと言えばバグなどの報告をしていただけるとありがたいです！

上記の通り、今後の方向性に関しては決定していません。そのため、機能のリクエストは今のところ受け付けていません。

## Releases

AC Libraryの最新版は、[AtCoder でのお知らせ](https://atcoder.jp/posts/518) でご覧いただけます。

また、[Release](https://github.com/atcoder/ac-library/releases)のページで全てのバージョンを確認することができます。

## ライセンス

- `atcoder` フォルダのヘッダファイルは [CC0](https://creativecommons.org/publicdomain/zero/1.0/legalcode) のライセンスの下でライセンスされています。
- TODO: 他のファイルのライセンスは決定していません。
