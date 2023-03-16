# AC(AtCoder) Library

AC Library is the official library of [AtCoder](https://atcoder.jp/home). This repository manages the contents of AC Library.

You may refer to the following links for more details:

- [The Announcement on AtCoder](https://atcoder.jp/posts/518)
- [The Announcement on Codeforces](https://codeforces.com/blog/entry/82400)
- [Practice Contest](https://atcoder.jp/contests/practice2)
- [AC Library Document(en)](https://atcoder.github.io/ac-library/production/document_en/)
- [AC Library Document(ja)](https://atcoder.github.io/ac-library/production/document_ja/)

The documents of master branch are as follows:

- [AC Library Document(en, master)](https://atcoder.github.io/ac-library/master/document_en/)
- [AC Library Document(ja, master)](https://atcoder.github.io/ac-library/master/document_ja/)

## Policy

Our goal of this project is to achieve that

- Enable **every AtCoder users** to use this library with **minimum efforts of studying about PC**
- Maximize convenience for **the usage in competitive programming**. We completely ignore other usages.
- No bugs. This is a fantasy, but we pursue this.

By this policy, we ignore some manners of C++ intentionally. For example,

- we don't use `size_t`, but use `int`.
- Segtree handles function pointers, not functional objects.
- and so on...

## Direction of this project

We haven't decided whether we should increase this library's contents or not because there are pros and cons.
If you are interested in this topic, please join the discussion in [The Announcement on Codeforces](https://codeforces.com/blog/entry/82400).

For now, we are not planning to add new features, and we use this repository only for

- collecting issues
- recording the changelogs
- versioning our releases

## Contributing

We accept issues/PRs **only from AtCoder users**.

We would appreciate it if you would report our mistakes like a typo, or, more importantly, bugs!

As mentioned above, we haven't decided which way to go. Therefore we are not accepting feature requests for now, and issues will be closed.

## Releases

You can view the newest version of AC Library in [The Announcement on AtCoder](https://atcoder.jp/posts/518) page.

You can also see all versions in [The Release](https://github.com/atcoder/ac-library/releases) page.

## License

This library is released under the [CC0](https://creativecommons.org/publicdomain/zero/1.0/legalcode), except for the third-party libraries that are located under `/document_(en|ja)/lib` directory. Please refer [/document_en/lib/LICENSE.md](./document_en/lib/LICENSE.md) for details.
