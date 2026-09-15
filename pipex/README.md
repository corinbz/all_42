# pipex

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

Reimplements what the shell does for `< infile cmd1 | cmd2 > outfile`,
without going through a shell: fork two child processes, connect their
stdin/stdout through a `pipe(2)`, and `execve` each command,
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
2. The parent creates a `pipe(2)` and `fork()`s two children
   (`child_one`, `child_two`).
   - `child_one` redirects stdin from `infile` and stdout to the pipe's
     write end, then calls `execve(cmd1)`.
   - `child_two` redirects stdin from the pipe's read end and stdout to
     `outfile`, then calls `execve(cmd2)`.
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

- No shell is involved: no globbing, no quoting rules, no built-ins.
  pipex treats `cmd1`/`cmd2` as a program name plus flags and passes
  them to `execve` directly.
