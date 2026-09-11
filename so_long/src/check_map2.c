/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:42:24 by corin             #+#    #+#             */
/*   Updated: 2024/04/24 10:45:05 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static bool	check_elements_count(t_count *count)
{
	if ((int)count->player != 1
		|| (int)count->exit != 1
		|| (int)count->collectible == 0)
		return (ft_error("Invalid elements count\n"), false);
	return (true);
}

static void	increment_elements(char cell, t_count *count)
{
	if (cell == 'P')
		count->player++;
	else if (cell == 'C')
		count->collectible++;
	else if (cell == 'E')
		count->exit++;
}

bool	count_elements(size_t row, size_t col, t_map *map)
{
	char	cell;
	t_count	count;

	count = (t_count){0};
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			cell = map->cell_value[row][col];
			if (cell == '1' || cell == '0')
			{
				col++;
				continue ;
			}
			else if (cell == 'P' || cell == 'C' || cell == 'E')
				increment_elements(cell, &count);
			else
				return (ft_error("Invalid character found\n"), false);
			col++;
		}
		row++;
	}
	return (check_elements_count(&count));
}
