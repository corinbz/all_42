# get_next_line

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

A function that reads a file (or any file descriptor: a regular file, a
pipe, `stdin`...) and returns it one line at a time, on successive
calls, without ever reading more of the underlying descriptor than
necessary. The classic 42 exercise in buffered I/O and static state.

## Signature

```c
char    *get_next_line(int fd);
```

Returns the next line (including the trailing `\n`, if present), or `NULL`
on EOF / error. Each call picks up exactly where the previous one on that
`fd` left off.

## How it works

- Each `read()` pulls `BUFFER_SIZE` bytes from `fd` (default `10`,
  overridable at compile time with `-D BUFFER_SIZE=n` to exercise both the
  large- and small-buffer code paths).
- A `static` buffer keeps any bytes read past the end of the current line
  between calls so they aren't re-read or dropped.
- `join_strs` appends freshly read data to the static remainder;
  `contains_newline` decides when a full line is ready to return.

## Files

| File | Role |
|------|------|
| `get_next_line.c` | Core `get_next_line` loop |
| `get_next_line_utils.c` | `join_strs`, `contains_newline`, `ft_free_all`, small string helpers |
| `get_next_line.h` | Prototypes, `BUFFER_SIZE` default |

## Build / use

There's no Makefile here. You copy `get_next_line` into another
project's source tree and compile it alongside, e.g.:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

`so_long` and `Cub3D` in this workspace reuse it as-is (or lightly
adapted) to parse their map files line by line.
