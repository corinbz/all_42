# push_swap

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

Sorts a stack of integers using only two stacks (`a`, `b`) and a fixed set
of stack operations, aiming for as few operations as possible. A second
program, `checker`, replays a sequence of operations against a stack and
reports whether the result is sorted.

## Usage

```sh
./push_swap 2 1 3 6 5 8
# prints the list of operations (one per line) that sorts stack a
```

## Allowed operations

| Op | Meaning |
|----|---------|
| `sa` / `sb` / `ss` | swap first two elements of `a` / `b` / both |
| `pa` / `pb` | push top of the other stack onto `a` / `b` |
| `ra` / `rb` / `rr` | rotate `a` / `b` / both, first element becomes last |
| `rra` / `rrb` / `rrr` | reverse-rotate `a` / `b` / both, last element becomes first |

## Algorithm

- **≤ 5 elements**: `sort_three`, `sort_four`, `sort_five` — hand-written
  optimal sequences for small stacks.
- **Larger stacks**: `radix_sort` — a binary radix sort adapted to the
  push/swap/rotate instruction set (`check_max_bits` determines how many
  passes are needed), pushing elements between `a` and `b` bit by bit
  rather than comparison-sorting.

Input is validated up front (`check_input.c`): must be a list of integers
representable as `long` within `INT_MIN`/`INT_MAX`, with no duplicates
(`are_duplicates`).

## Build

```sh
make        # builds push_swap (links a local copy of libft)
make clean
make fclean
make re
```

## Files

| File | Role |
|------|------|
| `main.c` | Entry point |
| `check_input.c` | Argument parsing and validation |
| `stack_intialization.c` / `stack_utils.c` / `stack_operations.c` | Doubly linked list stack + `sa`/`pa`/`ra`/... primitives |
| `radix_functions.c` | Radix-sort based algorithm for larger stacks |
| `smaller_five.c` | Optimal sorts for stacks of ≤ 5 |
| `errors.c` | Error / usage messages |
| `for_debugging.c` | Debug-only helpers (not part of the graded binary) |
| `push_swap.h` | `t_node` struct and prototypes |
| `libft/` | Vendored copy of [`Libft`](../Libft) |

## Testing operation counts

```sh
ARG="$(seq 1 100 | shuf | tr '\n' ' ')"
./push_swap $ARG | wc -l
```
