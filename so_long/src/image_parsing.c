/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:36:51 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/27 17:41:38 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static bool	resize_images(t_imgs assets)
{
	if (!mlx_resize_image(assets.player, assets.image_size, assets.image_size))
		return (false);
	if (!mlx_resize_image(assets.wall, assets.image_size, assets.image_size))
		return (false);
	if (!mlx_resize_image(assets.exit, assets.image_size, assets.image_size))
		return (false);
	if (!mlx_resize_image(assets.floor, assets.image_size, assets.image_size))
		return (false);
	if (!mlx_resize_image(assets.collectible, assets.image_size,
			assets.image_size))
		return (false);
	return (true);
}

bool	create_imgs(mlx_t *mlx, t_imgs assets)
{
	t_pngs pngs;
	
	pngs.player = mlx_load_png("img/player.png");
	pngs.wall = mlx_load_png("img/Blue.png");
	pngs.exit = mlx_load_png("img/exit.png");
	pngs.floor = mlx_load_png("img/floor.png");
	pngs.collectible = mlx_load_png("img/sandwich.png");
	assets.player = mlx_texture_to_image(mlx, pngs.player);
	assets.wall = mlx_texture_to_image(mlx, pngs.wall);
	assets.exit = mlx_texture_to_image(mlx, pngs.exit);
	assets.floor = mlx_texture_to_image(mlx, pngs.floor);
	assets.collectible = mlx_texture_to_image(mlx, pngs.collectible);
	mlx_delete_texture(pngs.player);
	mlx_delete_texture(pngs.wall);
	mlx_delete_texture(pngs.exit);
	mlx_delete_texture(pngs.floor);
	mlx_delete_texture(pngs.collectible);
	if (!resize_images(assets))
		return (ft_error("Failed to resize images\n"), false);
	return (true);
}

void	render_images(t_game *game)
{
	size_t	x_pos;
	size_t	y_pos;

	y_pos = 0;
	x_pos = 0;
	while (y_pos < game->map.height)
	{
		while (x_pos < game->map.width)
		{
			if (game->map.cell_value[y_pos][x_pos] == '1')
				draw_wall(game, x_pos, y_pos);
			else if (game->map.cell_value[y_pos][x_pos] == 'P')
				draw_player(game, x_pos, y_pos);
			else if (game->map.cell_value[y_pos][x_pos] == '0')
				draw_floor(game, x_pos, y_pos);
			else if (game->map.cell_value[y_pos][x_pos] == 'E')
				draw_exit(game, x_pos, y_pos);
			else if (game->map.cell_value[y_pos][x_pos] == 'C')
				draw_collectible(game, x_pos, y_pos);
			x_pos++;
		}
		x_pos = 0;
		y_pos++;
	}
}
