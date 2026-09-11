# Libft

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

Your own implementation of a subset of the C standard library, plus a
handful of extra helpers, packaged as a static library (`libft.a`). This is
the foundational project of the 42 curriculum: nearly every later C project
(`pipex`, `push_swap`, `so_long`, `Minishell`, `Philosophers`, `Cub3D`)
links against a copy of it.

## Build

```sh
make        # builds libft.a
make clean  # removes object files
make fclean # removes object files and libft.a
make re     # fclean + make
```

Link against it with `-Lft_lib -lft` (or wherever `libft.a` ends up) and
`#include "libft.h"`.

## Contents

### Libc replacements

| Category         | Functions |
|-------------------|-----------|
| `ctype`-style      | `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`, `ft_toupper`, `ft_tolower` |
| Memory             | `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`, `ft_calloc` |
| Strings            | `ft_strlen`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strnstr`, `ft_strlcpy`, `ft_strlcat`, `ft_strdup` |
| Conversion         | `ft_atoi`, `ft_itoa` |

### Additional (non-libc) functions

| Function | Purpose |
|----------|---------|
| `ft_substr` | Allocates and returns a substring from a given string |
| `ft_strjoin` | Concatenates two strings into a newly allocated string |
| `ft_strtrim` | Trims leading/trailing characters from a set |
| `ft_split` | Splits a string on a delimiter into a `NULL`-terminated array |
| `ft_strmapi` | Applies a function to each character of a string, building a new string |
| `ft_striteri` | Applies a function to each character of a string in place, with its index |
| `ft_putchar_fd` / `ft_putstr_fd` / `ft_putendl_fd` / `ft_putnbr_fd` | Output helpers that write directly to a file descriptor |

### Bonus: singly linked list (`t_list`)

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

## Notes

- Written to the 42 Norm (function length, no `for`/`while`/`switch`... style
  constraints, header format).
- Several other repos in this workspace (`pipex`, `push_swap`, `so_long`,
  `Minishell`) vendor their own copy of `libft` under a local `libft/`
  directory rather than depending on this one directly — that's normal for
  42 projects, which must be self-contained and buildable in isolation.
