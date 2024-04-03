/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:36:51 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/03 18:49:00 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

t_imgs	create_imgs(mlx_t *mlx, t_imgs assets)
{
	mlx_texture_t *player = mlx_load_png("img/player.png");
	mlx_texture_t *wall = mlx_load_png("img/Blue.png");
	mlx_texture_t *exit = mlx_load_png("img/exit.png");
	mlx_texture_t *floor = mlx_load_png("img/floor.png");
	mlx_texture_t *collectible = mlx_load_png("img/sandwich.png");
	// mlx_texture_t *won = mlx_load_png("img/you_won.png");
	assets.player = mlx_texture_to_image(mlx, player);
	assets.wall = mlx_texture_to_image(mlx, wall);
	assets.exit = mlx_texture_to_image(mlx, exit);
	assets.floor = mlx_texture_to_image(mlx, floor);
	assets.collectible = mlx_texture_to_image(mlx, collectible);
	// assets.won = mlx_texture_to_image(mlx, won);
	mlx_resize_image(assets.player, assets.image_size, assets.image_size);
	mlx_resize_image(assets.wall, assets.image_size, assets.image_size);
	mlx_resize_image(assets.exit, assets.image_size, assets.image_size);
	mlx_resize_image(assets.floor, assets.image_size, assets.image_size);
	mlx_resize_image(assets.collectible, assets.image_size, assets.image_size);
	// mlx_resize_image(assets.won, 64, 64);
	mlx_delete_texture(player);
	mlx_delete_texture(wall);
	mlx_delete_texture(exit);
	mlx_delete_texture(floor);
	mlx_delete_texture(collectible);
	// mlx_delete_texture(won);
	return (assets);
}

void render_images(t_game *game)
{
	size_t x_pos;
	size_t y_pos;
	
	y_pos = 0;
	x_pos = 0;
	// printf("img size is %zu\n",game->imgs.image_size);
	while(y_pos < game->map.height)
	{
		while(x_pos < game->map.width)
		{
			if(game->map.cell_value[y_pos][x_pos] == '1')
				draw_wall(game, x_pos, y_pos);
			else if(game->map.cell_value[y_pos][x_pos] == 'P')
			{
				draw_player(game, x_pos, y_pos);
			}
			else if(game->map.cell_value[y_pos][x_pos] == '0')
				draw_floor(game, x_pos, y_pos);
			else if(game->map.cell_value[y_pos][x_pos] == 'E')
				draw_exit(game, x_pos, y_pos);
			else if(game->map.cell_value[y_pos][x_pos] == 'C')
				draw_collectible(game, x_pos, y_pos);
			x_pos++;
		}
		x_pos = 0;
		y_pos++;
	}
	draw_score(game);
}
