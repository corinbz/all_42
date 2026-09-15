# Minishell

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

A simplified `bash`-like shell: reads a line, parses it into an AST of
pipes/redirections/commands, expands variables, and executes it, with its
own builtins and job control basics, built on `readline`.

## Usage

```sh
make
./minishell
minishell$ echo hello | grep h > out.txt
minishell$ export FOO=bar && echo $FOO   # (see "not implemented" below)
```

## Supported syntax

- **Pipes**: `cmd1 | cmd2 | cmd3`
- **Redirections**: `<`, `>`, `>>`, and heredoc `<< EOF`
- **Quoting**: single quotes (no expansion) and double quotes (`$VAR`
  expansion still applies)
- **Variable expansion**: `$VAR`, `$?` (last exit status)
- **Signals**: `Ctrl-C`, `Ctrl-\` handled to match bash's interactive
  behavior (prompt redraw, no shell exit)

## Builtins

`echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

Anything else is resolved against `PATH` (`get_path`) and run via
`fork`/`execve`.

Not implemented: `&&` / `||` / subshells `()`, wildcards (`*`), and
command substitution `` `cmd` `` / `$(cmd)`. This project's subject
excludes them.

## Architecture

1. **Parser** (`parse_cmd`, `parse_pipe`, `parse_exec`, `parse_redirections`):
   recursive-descent over the raw input line, building a small `t_cmd`
   AST (`t_exec_cmd` / `t_pipe_cmd` / `t_redir_cmd` / `t_heredoc_cmd`,
   tagged by `t_cmd_enum`).
2. **Expansion** (`expand_env_vars_and_quotes`, `expand_dollar_signs`,
   `expand_quotes`): walks tokens applying quoting and `$VAR`/`$?` rules
   with a small quote-state machine (`t_state`).
3. **Executor** (`exec_cmd`, `exec_pipe`, `exec_redir`, `exec_heredoc`):
   walks the AST, `fork`ing/`pipe`ing/redirecting file descriptors to
   match the tree shape, running builtins in-process where POSIX requires
   it (e.g. `cd`, `exit`) and everything else in a child.
4. **Environment** is a linked list (`t_link_list`) rather than the raw
   `envp` array, kept in sync by `export`/`unset`/`cd` and rebuilt into a
   `char **` (`link_list_to_array`) only when handing off to `execve`.

## Build

```sh
make        # builds minishell (links vendored libft + system readline)
make clean
make fclean
make re
```

Requires the `readline` development headers/library on the system
(`<readline/readline.h>`, `<readline/history.h>`).

## Files

| Path | Role |
|------|------|
| `src/minishell/main.c` | Entry point, prompt loop |
| `src/minishell/minishell_run*.c` | Terminal setup and the read, parse, expand, execute loop |
| `src/minishell/cmd_constructor.c` | AST node constructors |
| `src/minishell/parse_paths.c` | `PATH` resolution for external commands |
| `src/minishell/builtins_utils.c`, `envp_manipulation.c` | Builtin implementations, environment linked list |
| `src/minishell/signals.c` | `SIGINT`/`SIGQUIT` handling |
| `src/minishell/error_messages.c`, `free_utils*.c` | Error reporting and cleanup |
| `src/minishell/minishell.h` | Structs, enums, and full prototype list |
| `src/libft/` | Vendored copy of [`Libft`](../Libft) plus a linked-list module |
