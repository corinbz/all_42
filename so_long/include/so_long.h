/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:47:07 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/09 15:33:16 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/MLX42/include/MLX42/MLX42.h"
#include "../include/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
// #define WIDTH 1024
// #define HEIGHT 1024

typedef struct graphics
{
	mlx_texture_t *wall;
	mlx_texture_t *floor;
	mlx_texture_t *exit;
	mlx_image_t *player;
	mlx_texture_t *collectible;
}	t_graphics;

typedef struct s_map
{
	size_t width;
	size_t height;
	char **grid;
}	t_map;

//errors
void	ft_error(char *error_txt);

//map
t_graphics	create_graphics(mlx_t *mlx);

//hooks
void ft_hook(mlx_image_t image, mlx_t *mlx);

//map

void read_map(int fd, t_map *map);
void get_map_width(char *line, t_map *map);
void get_map_height(int fd, t_map *map);