/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:51:58 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/20 12:53:33 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static void	move_up(t_game *game, size_t pos_x, size_t pos_y)
{
	draw_floor(game, pos_x, pos_y);
	if (game->map.cell_value[pos_y][pos_x] == 'E')
		draw_exit(game, pos_x, pos_y);
	if (game->map.cell_value[pos_y - 1][pos_x] != '1')
	{
		if (game->map.cell_value[pos_y][pos_x] == 'C')
		{
			game->map.cell_value[pos_y][pos_x] = '0';
			game->count_collect -= 1;
		}
		if ((game->map.cell_value[pos_y - 1][pos_x] == 'E') &&
			(game->count_collect == 0))
			mlx_close_window(game->mlx);
		pos_y -= 1;
		game->moves += 1;
		printf("%zu moves\n", game->moves);
	}
	else
		ft_putstr_fd("OUCH!\n", 1);
	draw_player(game, pos_x, pos_y);
}

static void	move_down(t_game *game, size_t pos_x, size_t pos_y)
{
	draw_floor(game, pos_x, pos_y);
	if (game->map.cell_value[pos_y][pos_x] == 'E')
		draw_exit(game, pos_x, pos_y);
	if (game->map.cell_value[pos_y + 1][pos_x] != '1')
	{
		if (game->map.cell_value[pos_y][pos_x] == 'C')
		{
			game->map.cell_value[pos_y][pos_x] = '0';
			game->count_collect -= 1;
		}
		if ((game->map.cell_value[pos_y + 1][pos_x] == 'E') &&
			(game->count_collect == 0))
			mlx_close_window(game->mlx);
		pos_y += 1;
		game->moves += 1;
		printf("%zu moves\n", game->moves);
	}
	else
		ft_putstr_fd("OUCH!\n", 1);
	draw_player(game, pos_x, pos_y);
}

static void	move_left(t_game *game, size_t pos_x, size_t pos_y)
{
	draw_floor(game, pos_x, pos_y);
	if (game->map.cell_value[pos_y][pos_x] == 'E')
		draw_exit(game, pos_x, pos_y);
	if (game->map.cell_value[pos_y][pos_x - 1] != '1')
	{
		if (game->map.cell_value[pos_y][pos_x] == 'C')
		{
			game->map.cell_value[pos_y][pos_x] = '0';
			game->count_collect -= 1;
		}
		if ((game->map.cell_value[pos_y][pos_x - 1] == 'E') &&
			(game->count_collect == 0))
			mlx_close_window(game->mlx);
		pos_x -= 1;
		game->moves += 1;
		printf("%zu moves\n", game->moves);
	}
	else
		ft_putstr_fd("OUCH!\n", 1);
	draw_player(game, pos_x, pos_y);
}

static void	move_right(t_game *game, size_t pos_x, size_t pos_y)
{
	draw_floor(game, pos_x, pos_y);
	if (game->map.cell_value[pos_y][pos_x] == 'E')
		draw_exit(game, pos_x, pos_y);
	if (game->map.cell_value[pos_y][pos_x + 1] != '1')
	{
		if (game->map.cell_value[pos_y][pos_x] == 'C')
		{
			game->map.cell_value[pos_y][pos_x] = '0';
			game->count_collect -= 1;
		}
		if ((game->map.cell_value[pos_y][pos_x + 1] == 'E') &&
			(game->count_collect == 0))
			mlx_close_window(game->mlx);
		pos_x += 1;
		game->moves += 1;
		printf("%zu moves\n", game->moves);
	}
	else
		ft_putstr_fd("OUCH!\n", 1);
	draw_player(game, pos_x, pos_y);
}

void	ft_keyhooks(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_close_window(game->mlx);
	}
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
		move_up(game, game->player_pos.x, game->player_pos.y);
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
		move_down(game, game->player_pos.x, game->player_pos.y);
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		&& (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
		move_left(game, game->player_pos.x, game->player_pos.y);
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
		move_right(game, game->player_pos.x, game->player_pos.y);
}
