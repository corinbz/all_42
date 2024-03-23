/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:53:53 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/23 15:37:26 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

t_map create_map(void)
{
	t_map	map;

	map.width = 0;
	map.height = 0;
	map.valid = true;
	map.cell_value = ft_calloc(1, sizeof(char **));
	return (map);
}
void render_images(mlx_t *mlx, t_graphics graphics, t_map map)
{
	size_t x_position = 0;
	size_t y_position = 0;
	printf("map heigth is %zu width is %zu\n", map.height, map.width);
	while(y_position < map.height)
	{
		while(x_position <= map.width)
		{
			// printf("y: %zu x: %zu is %c\n",y_position ,x_position , map.cell_value[y_position][x_position]);
			// printf("%c", map.cell_value[y_position][x_position]);
			if(map.cell_value[y_position][x_position] == '1')
			{
				if(mlx_image_to_window(mlx, graphics.wall, x_position * 64, y_position * 64) < 0)
					ft_error("Failed to draw image to window");
			}
			else if(map.cell_value[y_position][x_position] == 'P')
			{
				if(mlx_image_to_window(mlx, graphics.floor, x_position * 64, y_position * 64) < 0)
					ft_error("Failed to draw image to window");
				if(mlx_image_to_window(mlx, graphics.player, x_position * 64, y_position * 64) < 0)
					ft_error("Failed to draw image to window");
			}
			else if(map.cell_value[y_position][x_position] == '0')
			{
				if(mlx_image_to_window(mlx, graphics.floor, x_position * 64, y_position * 64) < 0)
					ft_error("Failed to draw image to window");
			}
			else if(map.cell_value[y_position][x_position] == 'E')
			{
				if(mlx_image_to_window(mlx, graphics.floor, x_position * 64, y_position * 64) < 0)
					ft_error("Failed to draw image to window");
				if(mlx_image_to_window(mlx, graphics.exit, x_position * 64, y_position * 64) < 0)
					ft_error("Failed to draw image to window");
			}
			else if(map.cell_value[y_position][x_position] == 'C')
			{
				if(mlx_image_to_window(mlx, graphics.floor, x_position * 64, y_position * 64) < 0)
					ft_error("Failed to draw image to window");
				if(mlx_image_to_window(mlx, graphics.collectible, x_position * 64, y_position * 64) < 0)
					ft_error("Failed to draw image to window");
			}
			// printf("x: %zu, y: %zu\n", x_position, y_position);
			x_position++;
		}
		x_position = 0;
		y_position++;
	}
}