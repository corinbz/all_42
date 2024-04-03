/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:31:37 by corin             #+#    #+#             */
/*   Updated: 2024/04/03 18:39:42 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void draw_wall(t_game *game, size_t x_pos, size_t y_pos)
{
	if(mlx_image_to_window(game->mlx, game->imgs.wall, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
}

void draw_floor(t_game *game, size_t x_pos, size_t y_pos)
{
	if(mlx_image_to_window(game->mlx, game->imgs.floor, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
}

void draw_exit(t_game *game, size_t x_pos, size_t y_pos)
{
	if(mlx_image_to_window(game->mlx, game->imgs.floor, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
	if(mlx_image_to_window(game->mlx, game->imgs.exit, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
}

void draw_player(t_game *game, size_t x_pos, size_t y_pos)
{
	if(mlx_image_to_window(game->mlx, game->imgs.floor, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
	if(mlx_image_to_window(game->mlx, game->imgs.player, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
	game->player_pos.x = x_pos;
	game->player_pos.y = y_pos;
}
void draw_collectible(t_game *game, size_t x_pos, size_t y_pos)
{
	if(mlx_image_to_window(game->mlx, game->imgs.floor, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
	if(mlx_image_to_window(game->mlx, game->imgs.collectible, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
	game->count_collect += 1;
}