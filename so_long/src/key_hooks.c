/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:51:58 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/24 19:21:41 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static void move_up(t_game *game)
{
	if(mlx_image_to_window(game->mlx, game->imgs.floor, game->player_pos.x * 64, game->player_pos.y * 64) < 0)
		ft_error("Failed to draw image to window");
	if(game->map.cell_value[game->player_pos.y - 1][game->player_pos.x] != '1')
		game->player_pos.y -= 1;
	else
		ft_putstr_fd("OUCH!\n", 1);
	if(mlx_image_to_window(game->mlx, game->imgs.player, game->player_pos.x * 64, game->player_pos.y * 64) < 0)
		ft_error("Failed to draw image to window");
}
static void move_down(t_game *game)
{
	if(mlx_image_to_window(game->mlx, game->imgs.floor, game->player_pos.x * 64, game->player_pos.y * 64) < 0)
		ft_error("Failed to draw image to window");
	if(game->map.cell_value[game->player_pos.y + 1][game->player_pos.x] != '1')
		game->player_pos.y += 1;
	else
		ft_putstr_fd("OUCH!\n", 1);
	if(mlx_image_to_window(game->mlx, game->imgs.player, game->player_pos.x * 64, game->player_pos.y * 64) < 0)
		ft_error("Failed to draw image to window");
}

static void move_left(t_game *game)
{
	if(mlx_image_to_window(game->mlx, game->imgs.floor, game->player_pos.x * 64, game->player_pos.y * 64) < 0)
		ft_error("Failed to draw image to window");
	if(game->map.cell_value[game->player_pos.y][game->player_pos.x - 1] != '1')
		game->player_pos.x -= 1;
	else
		ft_putstr_fd("OUCH!\n", 1);
	if(mlx_image_to_window(game->mlx, game->imgs.player, game->player_pos.x * 64, game->player_pos.y * 64) < 0)
		ft_error("Failed to draw image to window");
}
static void move_right(t_game *game)
{
	if(mlx_image_to_window(game->mlx, game->imgs.floor, game->player_pos.x * 64, game->player_pos.y * 64) < 0)
		ft_error("Failed to draw image to window");
	if(game->map.cell_value[game->player_pos.y][game->player_pos.x + 1] != '1')
		game->player_pos.x += 1;
	else
		ft_putstr_fd("OUCH!\n", 1);
	if(mlx_image_to_window(game->mlx, game->imgs.player, game->player_pos.x * 64, game->player_pos.y * 64) < 0)
		ft_error("Failed to draw image to window");
}

void ft_keyhooks(mlx_key_data_t keydata, void* param)
{
	t_game *game;
	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		move_up(game);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		move_down(game);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		move_left(game);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		move_right(game);
}