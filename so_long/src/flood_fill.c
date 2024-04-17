/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:42:00 by corin             #+#    #+#             */
/*   Updated: 2024/04/14 18:26:37 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	flood_fill(size_t row, size_t col, size_t col_cnt, t_game game)
{
	if (row > game.map.height -1 || row > game.map.width -1
		|| game.map.visited_cell[row][col] == 'v'
		|| game.map.cell_value[row][col] == '1')
		return ;
	game.map.visited_cell[row][col] = 'v';
	if (game.map.cell_value[row][col] == 'C')
		col_cnt--;
	flood_fill (row -1, col, col_cnt, game);
	flood_fill (row +1, col, col_cnt, game);
	flood_fill (row, col -1, col_cnt, game);
	flood_fill (row, col +1, col_cnt, game);
}

bool	collectibles_accesible(t_game *game)
{
	size_t	total_coll;

	total_coll = game->count_collect;
	printf("total collectibles: %zu", total_coll);
	//flood_fill(game->player_pos.x, game->player_pos.y, total_coll, *game);
	return (true);
}
