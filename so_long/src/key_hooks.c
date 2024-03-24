/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:51:58 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/24 11:01:01 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void move_up(t_game *game)
{
	
}

void ft_keyhooks(mlx_key_data_t keydata, void* param)
{
	t_game *game;
	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		puts("UP");
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		puts("DOWN");
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		puts("LEFT");
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		puts("RIGHT");
}