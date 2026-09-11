/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:36:51 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/28 11:26:21 by ccraciun         ###   ########.fr       */
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

static bool	load_pngs(t_pngs *pngs)
{
	pngs->player = mlx_load_png("img/player.png");
	if (!pngs->player)
		return (ft_error("Failed to load player\n"), false);
	pngs->wall = mlx_load_png("img/Blue.png");
	if (!pngs->wall)
		return (ft_error("Failed to load wall\n"), false);
	pngs->exit = mlx_load_png("img/exit.png");
	if (!pngs->exit)
		return (ft_error("Failed to load exit\n"), false);
	pngs->floor = mlx_load_png("img/floor.png");
	if (!pngs->floor)
		return (ft_error("Failed to load floor\n"), false);
	pngs->collectible = mlx_load_png("img/sandwich.png");
	if (!pngs->collectible)
		return (ft_error("Failed to load collectible\n"), false);
	return (true);
}

bool	create_imgs(t_game *game)
{
	t_pngs	pngs;

	if (!load_pngs(&pngs))
		return (free_game(game), mlx_terminate(game->mlx), exit(1), false);
	game->imgs.player = mlx_texture_to_image(game->mlx, pngs.player);
	game->imgs.wall = mlx_texture_to_image(game->mlx, pngs.wall);
	game->imgs.exit = mlx_texture_to_image(game->mlx, pngs.exit);
	game->imgs.floor = mlx_texture_to_image(game->mlx, pngs.floor);
	game->imgs.collectible = mlx_texture_to_image(game->mlx, pngs.collectible);
	mlx_delete_texture(pngs.player);
	mlx_delete_texture(pngs.wall);
	mlx_delete_texture(pngs.exit);
	mlx_delete_texture(pngs.floor);
	mlx_delete_texture(pngs.collectible);
	if (!resize_images(game->imgs))
		ft_error("Failed to resize images\n");
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
