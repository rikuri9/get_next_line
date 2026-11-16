*This project has been created as part of the 42 curriculum by riwamoto.*

# get_next_line

## Description

get_next_lineは、ファイルディスクリプタから読み込んだ1行を返す関数である。

読むものが残っていない、またはエラーが発生した場合 `NULL` を返す

```c
char	*get_next_line(int fd)
```

| 引数 | 説明 |
|---|---|
| fd | 読み込むファイルディスクリプタ（ファイル、標準出力）|

| 戻り値 | 条件 |
|---|---|
| 読み込んだ1行 | 改行 `\n` を含む。ファイル末尾に改行がない場合、改行なしの最後の行を返す |
| `NULL` | 読み込むものがない、またはエラーが発生した場合 |

返された文字列は `malloc` で確保されているため、呼び出し側で `free` する必要がある。

一回の `read` で読み込むバイト数は `BUFFER_SIZE` で決まる。既定値は `42` で、コンパイル時に `-D BUFFER_SIZE=n` (nは1以上の正の値)で変更できる

**目的**

* C言語におけるstatic変数に対する理解
* ファイルディスクリプタと `read` の扱いの理解
* 今後の課題で使用するための自分用のライブラリの作成

## Instructions

### Directory structure

```
project/
├── get_next_line_utils.c     # ft_strlen, has_newline, join_chunk, line_len
├── get_next_line.c           # read_to_stash, extract_line, trim_stash, get_next_line
├── get_next_line.h
└── README.md
```

### Usage

main.c を作成し以下を記載

```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	fd = 0;
	if (argc >= 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	if (fd > 0)
		close(fd);
	return (0);
}
```

### Complie

#### ⚠ 注意： Makefile はありません

このリポジトリには `Makefile` が含まれていません（課題要件より）。

`make` は使えないため以下のコマンドを直接実行（test.txtは自身で作成）。

```bash
cc -Wall -Wextra -Werror main.c get_next_line*.c
./a.out test.txt
```

BUFFER_SIZEを指定する場合は以下を実行

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<数値> main.c get_next_line*.c
./a.out test.txt
```

### Algorithm

#### 処理の流れ

`static` 変数 `stash` に、読み込んだがまだ返していない文字列を保持させる。

1度の呼び出しに対して次の3段階で処理する。

1. **read_to_stash** `stash` に改行が含まれていなければ、`BUFFER_SIZE` バイトずつ `read` して `stash` の末尾に連結する。改行を含むデータを呼んだ場合、またはEOF・エラーの時点で読み込みを停止する。

2. **extract_line** `stash` の先頭から改行まで（改行含む）を新しい文字列として取り出す。改行がなければ末尾までを取り出す。

3. **trim_stash** 返した行の分を `stash` から取り出し残りを新しい領域に移す。残りがなければ 'stash' を 'free' して `NULL` にする。

#### エラー時の動作

* `fd` が負の値、または `BUFFER_SIZE` が0以下の場合は何もせず `NULL` を返す。
* `read` がエラーを返した場合、 `stash` を `free` して `NULL` を返す。

#### この方針の利点

* 改行が見つかった時点で `read` を停止するため、ファイルを必要以上に読み込まない。
* 返せず残ったデータを `stash` に残すことで、次回の呼び出しでそのまま使用できる。
* 読み込みのバッファを `malloc` で確保しているため、`BUFFER_SIZE` が大きくなってもスタックを使い切らない

#### この方針の弱点

* 連結のたびに `stash` 全体を新しい領域にコピーするため、`BUFFER_SIZE` が小さいかつ、1行が長いと処理時間が長くなる。

通常のテキストファイルでは問題にならないと判断したため、課題の範囲ではこの方針で十分だと判断した。

## Resources

### Reference material

- [C言語教室　第33回　static ってなにさ？](https://note.com/kazushinakamura/n/n981fcf8d0546) : `static` 変数の性質の理解に使用
- [bash で単体テスト](https://qiita.com/waterada/items/98a3c01c7ad88e97595f) : 動作確認用テストの作成に使用
- [長い文字列作成ツール](https://tools.m-bsys.com/ex/long_text_maker.php#google_vignette) : テストのためのファイル作成に使用

### How AI was used

- プログラム内でのstatic変数の動きの視覚化するために使用した。
- READMEのレビューするために使用した。