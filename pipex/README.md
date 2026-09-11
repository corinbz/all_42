# pipex

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

Reimplements what the shell does for `< infile cmd1 | cmd2 > outfile`,
without going through a shell: fork two child processes, wire their
stdin/stdout together through a `pipe(2)`, and `execve` each command,
resolving it against `PATH` by hand.

## Usage

```sh
./pipex infile cmd1 cmd2 outfile
# equivalent to:
< infile cmd1 | cmd2 > outfile
```

## How it works

1. `create_and_open_files` opens `infile` (read) and `outfile`
   (write/create/truncate).
2. A `pipe(2)` is created; two children are `fork()`ed
   (`child_one`, `child_two`).
   - `child_one`: stdin ← `infile`, stdout → pipe write end, then
     `execve(cmd1)`.
   - `child_two`: stdin ← pipe read end, stdout → `outfile`, then
     `execve(cmd2)`.
3. The parent closes its own fds and `waitpid`s on both children.
4. Command resolution (`get_commands_path`) walks `PATH` from `envp`
   looking for an executable match, unless the command is given as an
   absolute/relative path already (`is_cmd_absolute_path`).

## Build

```sh
make        # builds pipex (links a local copy of libft)
make clean
make fclean
make re
```

## Files

| File | Role |
|------|------|
| `pipex.c` / `main.c` | Entry point, orchestration |
| `parse_input.c` / `parse_input2.c` | Command/argument parsing, `PATH` resolution |
| `file_handling.c` | Opening `infile`/`outfile` |
| `error_handling.c` | Argument-count and access-error checks |
| `mem_free.c` | Cleanup of the `t_data` structure |
| `pipex.h` | `t_data` struct and prototypes |
| `libft/` | Vendored copy of [`Libft`](../Libft) |

## Notes

- No shell is involved: no globbing, no quoting rules, no built-ins —
  `cmd1`/`cmd2` are taken as a program name plus flags, resolved via
  `execve` directly.
