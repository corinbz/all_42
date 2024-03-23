/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:53:53 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/21 20:05:36 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

t_graphics	create_graphics(mlx_t *mlx)
{
	t_graphics	assets;

	mlx_texture_t *player = mlx_load_png("img/player.png");
	mlx_texture_t *wall = mlx_load_png("img/Blue.png");
	assets.player = mlx_texture_to_image(mlx, player);
	assets.wall = mlx_texture_to_image(mlx, wall);
	mlx_resize_image(assets.player, 64, 64);
	mlx_resize_image(assets.wall, 64, 64);
	mlx_delete_texture(player);
	mlx_delete_texture(wall);
	return (assets);
}
t_map create_map(void)
{
	t_map	map;

	map.width = 0;
	map.height = 0;
	map.valid = true;
	return (map);
}
void render_images(mlx_t *mlx, t_graphics graphics, t_map map)
{
	size_t position = 0;
	while(position < map.width)
	{
		if(mlx_image_to_window(mlx, graphics.wall, position * 64, 0) < 0)
			ft_error("Failed to draw image to window");
		position++;
	}
}