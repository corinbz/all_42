/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:47:07 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/23 10:21:04 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIBS/LIBFT/libft.h"
#include "../LIBS/MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE		1
#define ALLOC_FAIL		2
#define READ_FILE_ERR	3
#define MAX_MAP_HEIGHT	20
#define MAX_MAP_WIDTH	40

typedef struct s_count
{
	size_t	player;
	size_t	exit;
	size_t	collectible;
}	t_count;

typedef struct s_screen
{
	size_t	width;
	size_t	height;
}	t_screen;

typedef struct s_imgs
{
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*exit;
	mlx_image_t	*player;
	mlx_image_t	*collectible;
	mlx_image_t	*score;
	size_t		image_size;
}	t_imgs;

typedef struct s_map
{
	char	**cell_value;
	size_t	width;
	size_t	height;
	bool	valid;
}	t_map;

typedef struct s_player_pos
{
	size_t	x;
	size_t	y;
}	t_player_pos;

typedef struct s_game
{
	mlx_t					*mlx;
	t_player_pos			player_pos;
	t_map					map;
	t_screen				screen;
	t_imgs					imgs;
	size_t					count_collect;
	size_t					moves;
	char					*map_name;
}	t_game;

//errors
void	ft_error(char *error_txt);

//imgs
t_imgs	create_imgs(mlx_t *mlx, t_imgs assets);
void	render_images(t_game *game);

//draw_images
void	draw_wall(t_game *game, size_t x_pos, size_t y_pos);
void	draw_floor(t_game *game, size_t x_pos, size_t y_pos);
void	draw_exit(t_game *game, size_t x_pos, size_t y_pos);
void	draw_player(t_game *game, size_t x_pos, size_t y_pos);
void	draw_collectible(t_game *game, size_t x_pos, size_t y_pos);

//hooks
void	ft_keyhooks(mlx_key_data_t keydata, void *param);

//data_parsing
t_map	create_map(void);
bool	parse_map(t_map *map, char *map_filename);
bool	get_map_elements(t_map *map, char *map_filename);
void	init_game_struct (t_game *game, char* map_name);
void	start_game(t_game *game);

//cleaning
void	free_game(t_game *game);

//utils
char	*get_next_line(int fd);
void	ft_free_all(char **str1, char **str2, char **str3);
int		contains_newline(const char *s);
char	*join_strs(const char *s1, const char *s2);

bool	collectibles_accesible(t_game *game);