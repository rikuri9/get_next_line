*This project has been created as part of the 42 curriculum by riwamoto.*

# get_next_line

## Description

get_next_lineは、ファイルディスクリプタから読み込んだ1行を返す関数である。

**目的**

* C言語におけるstatic変数に対する理解
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

main.c に以下を記載

```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

## ⚠ 注意： Makefile はありません

このリポジトリには `Makefile` が含まれていません（課題要件より）。

`make` は使えないため以下のコマンドを直接実行。

```bash
cc -Wall -Wextra -Werror main.c get_next_line*.c
./a.out
```

## Resources

### Reference material



### How AI was used

- 