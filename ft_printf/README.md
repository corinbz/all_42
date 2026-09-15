# ft_printf

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

A from-scratch reimplementation of a subset of the standard `printf`,
built as a static library (`libftprintf.a`) using variadic arguments
(`<stdarg.h>`).

## Signature

```c
int ft_printf(const char *format, ...);
```

Returns the number of characters printed (matching `printf`'s contract),
or a negative value on error.

## Supported conversions

| Specifier | Meaning |
|-----------|---------|
| `%c` | character |
| `%s` | string |
| `%p` | pointer address (hex, `0x`-prefixed) |
| `%d` / `%i` | signed decimal integer |
| `%u` | unsigned decimal integer |
| `%x` | unsigned hex, lowercase |
| `%X` | unsigned hex, uppercase |
| `%%` | literal `%` |

## Build

```sh
make        # builds libftprintf.a
make clean
make fclean
make re
```

## Files

| File | Role |
|------|------|
| `src/ft_printf.c` | Format-string parser / dispatcher |
| `src/ft_putstr.c` / `ft_putnbr.c` / `ft_put_uns_nbr.c` | `%s`, `%d`/`%i`, `%u` handlers |
| `src/ft_put_hex.c` | `%x` / `%X` handler |
| `src/ft_putadress.c` | `%p` handler |
| `src/ft_strlen.c` | Local `strlen`, used for the return-value character count |
| `include/ft_printf.h` | Public prototypes |

## Usage

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("%s is %d years old (%%p = %p)\n", "libft", 2, (void *)&main);
    return (0);
}
```

Compile against the library with `-L. -lftprintf` after `#include "ft_printf.h"`.
