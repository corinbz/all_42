# Cub3D

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

A ray-casted, Wolfenstein-3D-style first-person renderer: parses a `.cub`
map/config file, then renders textured walls, floor and ceiling in
real time from a movable first-person camera, using
[MLX42](MLX42) for the window/graphics layer.

## Usage

```sh
./cub3d assets/maps/subject_map.cub
```

- **Move**: `W` `A` `S` `D`
- **Turn**: `←` `→` (and/or mouse look, via `mouse_handler`)
- **Quit**: `ESC` / window close

## `.cub` file format

```
NO ./textures/wall_n.png
SO ./textures/wall_s.png
WE ./textures/wall_w.png
EA ./textures/wall_e.png
F 220,100,0
C 225,30,0

1111111111111
1000000000001
1000P00000001
1111111111111
```

- `NO`/`SO`/`WE`/`EA`: paths to the four wall textures (`parse_img_paths.c`).
- `F` / `C`: floor / ceiling RGB colors (`parse_colors.c`).
- The map grid: `1` wall, `0` walkable floor, `N`/`S`/`E`/`W` player start +
  facing direction; unreachable/space cells are allowed only where they
  can't leak outside the map (`check_map_space.c`, `check_map_lines.c`).

`assets/maps/` holds a range of valid and deliberately malformed sample
maps used to exercise the parser (`check_map_basic.c`,
`check_map_lines.c`, `check_map_space.c`).

## Rendering

`raycast.c` casts one ray per screen column using the DDA algorithm
(`delta_dist_x/y`, `side_dist_x/y`) against the map grid, determines the
perpendicular wall distance to avoid fish-eye distortion, and
`render_wall_texture.c` picks the correct texture (`wall_n/s/e/w`) and
texture-space `x` offset based on which side/face was hit.

## Build

```sh
make        # builds cub3d (builds/links MLX42, then links vendored libft utils)
make clean
make fclean
make re
```

## Files

| File | Role |
|------|------|
| `src/main.c` | Entry point |
| `src/prepare_game.c` | Loads textures, allocates the render buffer |
| `src/game_loop.c` | Per-frame update (movement, redraw) |
| `src/raycast.c` | Core DDA ray-casting |
| `src/render_wall_texture.c` | Texture sampling per screen column |
| `src/keys_handlers.c` / `mouse_handler.c` | Input handling |
| `src/map_parsing/` | `.cub` file parsing and validation |
| `src/utilities/` | Vendored string/memory/`get_next_line` helpers |
| `include/cub3d.h` | Structs (`t_game`, `t_map`, `t_data`, `t_textures`) and prototypes |
| `MLX42/` | Vendored [MLX42](https://github.com/codam-coding-college/MLX42) graphics library |
| `assets/`, `textures/` | Sample maps and wall textures |
