# 42 Projects

![42](https://img.shields.io/badge/42-cursus-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/language-C-blue?style=flat-square)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)

A single repository collecting every project from the 42 School common
core. Each folder below is independent — its own Makefile, its own
README — grouped here for one clean portfolio history.

## Piscine / early C

| Project | Description |
|---|---|
| [Libft](Libft) | Custom C standard library subset, the foundation every later C project links against |
| [get_next_line](get_next_line) | Read a file descriptor one line at a time, buffered, using static state |
| [ft_printf](ft_printf) | Reimplementation of `printf` (`%s %c %p %d %i %u %x %X %%`) |
| [pipex](pipex) | Reimplements `< in cmd1 \| cmd2 > out` with `fork`/`pipe`/`execve` |
| [push_swap](push_swap) | Sorts a stack with only push/swap/rotate ops, radix sort for large inputs |

## System programming

| Project | Description |
|---|---|
| [Philosophers](Philosophers) | Dining philosophers problem: threads, mutexes, starvation detection |
| [Minishell](Minishell) | A `bash`-like shell: parsing, pipes, redirections, expansion, builtins |

## Graphics

| Project | Description |
|---|---|
| [so_long](so_long) | Small 2D tile game (MLX42): collect items, reach the exit |
| [Cub3D](Cub3D) | Ray-casted first-person renderer (MLX42), Wolfenstein-3D style |

## C++ modules (CPP00 – CPP09)

| Module | Topic |
|---|---|
| [CPP00](CPP00) | Namespaces, classes, member functions |
| [CPP01](CPP01) | Memory allocation, references, pointers |
| [CPP02](CPP02) | Ad-hoc polymorphism, Orthodox Canonical Form, operator overloading |
| [CPP03](CPP03) | Inheritance |
| [CPP04](CPP04) | Subtype polymorphism, abstract classes |
| [CPP05](CPP05) | Repetition and exceptions |
| [CPP06](CPP06) | Casts |
| [CPP07](CPP07) | Templates |
| [CPP08](CPP08) | Templated containers, STL |
| [CPP09](CPP09) | STL (`map`, `stack`, and the Ford–Johnson sort) |

## Web

| Project | Description |
|---|---|
| [Webserv](Webserv) | HTTP/1.1 server from scratch: `poll()` event loop, config file, CGI, uploads |

## Ops

| Project | Description |
|---|---|
| [Inception](Inception) | Multi-container infra (NGINX + WordPress/PHP-FPM + MariaDB) via Docker Compose |

## Building

There's no top-level build — each project builds on its own:

```sh
cd <project> && make
# CPP modules build per exercise:
cd CPP0X/exYY && make
```
