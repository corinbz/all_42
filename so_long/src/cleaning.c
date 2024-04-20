/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:19:52 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/20 12:22:31 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static bool	free_map(t_game *game)
{
	ft_free_2d(game->map.cell_value);
	return (true);
}

void	free_game(t_game *game)
{
	free_map(game);
	free(game->map_name);
}
