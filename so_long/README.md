# so_long

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

A small 2D tile-based game built with the [MLX42](LIBS/MLX42) graphics
library: guide the player across a map, collect every collectible, then
reach the exit in the fewest moves possible.

## Usage

```sh
make    # fetches the MLX42 submodule and builds it with CMake on first run
./so_long maps/map.ber
```

Move with the arrow keys (or `W`/`A`/`S`/`D`). The game prints the move
counter to the terminal on every move. `ESC` or the window's close button
exits cleanly.

## Map format (`.ber`)

A rectangular grid of characters:

| Char | Meaning |
|------|---------|
| `1` | wall |
| `0` | floor |
| `P` | player start (exactly one) |
| `C` | collectible (at least one) |
| `E` | exit (exactly one) |

`maps/` contains a valid sample map; `maps/invalid/` is a set of
deliberately broken maps (missing player/exit, unclosed walls, unreachable
collectibles, non-rectangular shape, wrong extension...) used to exercise
`parse_map`/`check_map*` validation.

## Validation rules enforced before the window opens

- Rectangular (every row the same length).
- Surrounded by walls on every edge.
- Exactly one player, at least one collectible, at least one exit.
- Every collectible and the exit reachable from the player's start
  position (`flood_fill`).

## Build

```sh
make        # builds so_long (links vendored libft + MLX42)
make clean
make fclean
make re
```

## Files

| File | Role |
|------|------|
| `src/main.c` | Entry point, MLX init, game loop hookup |
| `src/check_map.c` / `check_map2.c` | Structural map validation |
| `src/flood_fill.c` | Reachability check for collectibles/exit |
| `src/image_parsing.c` / `draw_images.c` | Loading & blitting sprites (`img/`) |
| `src/key_hooks.c` | Keyboard input, move counting, win condition |
| `src/init_structs.c` | `t_game` setup |
| `src/get_next_line*.c` | Line-by-line map file reading |
| `src/cleaning.c` / `errors.c` | Cleanup and error reporting |
| `headers/so_long.h` | Structs (`t_game`, `t_map`, `t_imgs`...) and prototypes |
| `LIBS/LIBFT/` | Vendored copy of [`Libft`](../Libft) |
| `LIBS/MLX42/` | Vendored [MLX42](https://github.com/codam-coding-college/MLX42) graphics library |
