Eratosthenes の篩の高速化
===============

Eratosthenes の篩を実装、高速化していくコードを置いていきます。詳細は [Qiita](https://qiita.com/tags/%E3%82%A8%E3%83%A9%E3%83%88%E3%82%B9%E3%83%86%E3%83%8D%E3%82%B9%E3%81%AE%E7%AF%A9) に

- [エラトステネスの篩の高速化](https://qiita.com/peria/items/a4ff4ddb3336f7b81d50)
- [エラトステネスの篩の高速化 (2)](https://qiita.com/peria/items/54499b9ce9d5c1e93e5a)
- [エラトステネスの篩の高速化 (3)](https://qiita.com/peria/items/e0ab38f95d16a5f7cc58)
- [エラトステネスの篩の高速化 (4)](https://qiita.com/peria/items/7c62831ad9781c7c1577)
- [エラトステネスの篩の高速化 (5)](https://qiita.com/peria/items/ffc58b31470ad3297567)
- [エラトステネスの篩の高速化 (6)](https://qiita.com/peria/items/c1d8523342e81bb23375)

使い方
-----

`make` すればコンパイルしてくれるはずです。C++11 に対応した clang と [gflags](https://github.com/gflags/gflags) が必要です。
`Makefile` も難しいことはしてないはずなのでコンパイラを変えたければ適当に書き直してください。

実行時は呼び出し方に対応した 3 パターンの挙動があります。

```
$ eratosthenes [--generator=v] [--time_limit=t]
$ eratosthenes x [--generator=v]
$ eratosthenes x y [--generator=v]
```

引数がない場合、いくつか既知の数値を使って出力テストとパフォーマンス計測を行います。パフォーマンス計測とか言いつつ 1 回しか計測してません。
篩にあまり時間がかかると待ってられないので 5 秒かかったものはそれ以上のテストを行わないようにしています。この制限時間はオプション引数として
--time_limit` で設定できます。

引数が 1 つの場合、`x` 以下の素数を求め(ただし出力はしない) その個数を数えて出力します。ついでに時間計測をします。
多分これが一番メジャーな使いみちだと思います。

引数が 2 つの場合は `x` 以上 `y` 以下の素数を求め、その個数を出力します。

いずれの場合もオプション引数として `--generator` を指定すると素数を求めるルーチンにバージョン `v` のものを利用します。
バージョン番号は上記 Qiita の記事やコード内クラス名や `version()` メソッドに書かれてます。実はいろいろ処理する前に表示もさせてます。
指定がない場合は最新版(多くの場合最速)を使います。
