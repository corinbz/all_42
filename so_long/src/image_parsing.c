/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:36:51 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/23 15:37:16 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

t_graphics	create_graphics(mlx_t *mlx)
{
	t_graphics	assets;

	mlx_texture_t *player = mlx_load_png("img/player.png");
	mlx_texture_t *wall = mlx_load_png("img/Blue.png");
	mlx_texture_t *exit = mlx_load_png("img/exit.png");
	mlx_texture_t *floor = mlx_load_png("img/floor.png");
	mlx_texture_t *collectible = mlx_load_png("img/sandwich.png");
	assets.player = mlx_texture_to_image(mlx, player);
	assets.wall = mlx_texture_to_image(mlx, wall);
	assets.exit = mlx_texture_to_image(mlx, exit);
	assets.floor = mlx_texture_to_image(mlx, floor);
	assets.collectible = mlx_texture_to_image(mlx, collectible);
	mlx_resize_image(assets.player, 64, 64);
	mlx_resize_image(assets.wall, 64, 64);
	mlx_resize_image(assets.exit, 64, 64);
	mlx_resize_image(assets.floor, 64, 64);
	mlx_resize_image(assets.collectible, 64, 64);
	mlx_delete_texture(player);
	mlx_delete_texture(wall);
	mlx_delete_texture(exit);
	mlx_delete_texture(floor);
	mlx_delete_texture(collectible);
	return (assets);
}