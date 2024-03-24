/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:47:07 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/24 10:24:47 by corin            ###   ########.fr       */
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

#define	BUFFER_SIZE		10
#define	ALLOC_FAIL		2
#define	READ_FILE_ERR	3

typedef struct s_screen
{
	size_t	width;
	size_t	height;
}	t_screen;

typedef struct s_graphics
{
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*exit;
	mlx_image_t	*player;
	mlx_image_t	*collectible;
	size_t		image_size;
}	t_graphics;

typedef struct s_map
{
	char	**cell_value;
	size_t	width;
	size_t	height;
	bool	valid;
}	t_map;

typedef struct s_player_coordonates
{
	size_t	x;
	size_t	y;	
}	t_player_coordonates;

typedef struct s_game
{
	mlx_t	*mlx;
	t_player_coordonates player_coordonates;
	t_map map;
	t_screen screen;
	t_graphics graphics;
}	t_game;

//errors
void	ft_error(char *error_txt);

//graphics
t_graphics	create_graphics(mlx_t *mlx, t_graphics assets);
void		render_images(mlx_t *mlx, t_graphics graphics, t_map map);

//hooks
void ft_keyhooks(mlx_key_data_t keydata, void* param);

//data_parsing
t_map	create_map(void);
void	parse_map(t_map *map);
void	get_map_elements(t_map *map);
void	init_game_struct(t_game *game);
void	start_game(t_game *game);

//utils
char	*get_next_line(int fd);
void	ft_free_all(char **str1, char **str2, char **str3);
int		contains_newline(const char *s);
char	*join_strs(const char *s1, const char *s2);