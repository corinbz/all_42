/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:41:30 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/05 15:45:54 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static bool	map_size_valid(int fd, t_map *map)
{
	char	*line;
	size_t	len;

	line = get_next_line(fd);
	len = ft_line_len(line);
	map->width = len;
	free(line);
	while ((line = get_next_line(fd)))
	{
		len = ft_line_len(line);
		if (len != map->width)
			return (free(line), false);
		map->height++;
		free(line);
	}
	// printf("h: %zu, w: %zu\n",map->height, map->width);
	if(map->height <= MAX_MAP_HEIGHT && map->width <= MAX_MAP_WIDTH)
		return(free(line), true);
	return(free(line), false);
}

static bool check_walls(size_t row, size_t col, t_map *map) {
	while (row < map->height)
	{
		if (col == 0 || col == map->width - 1)
		{
			if ((map->cell_value[row][col]) != '1')
				return (false);
		}
		else
		{
			if (row == 0 || row == map->height - 1)
			{
				if ((map->cell_value[row][col]) != '1')
					return (false);
			}
		}
		col++;
		if (col == map->width)
		{
			col = 0;
			row++;
		}
	}
	return (true);
}

static bool	check_elements_count(t_count *count)
{
	if ((int)count->player != 1
		|| (int)count->exit != 1
		|| (int)count->collectible == 0)
		return (false);
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

static bool	count_elements(size_t row, size_t col, t_map *map)
{
	char	cell;
	t_count	count;

	count = (t_count){0};
	while (row <= map->height)
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
				return (false);
			col++;
		}
		row++;
	}
	return (check_elements_count(&count));
}

static bool	check_map_elements(t_map *map)
{
	bool	res;
	size_t	row;
	size_t	col;

	res = true;
	row = 0;
	col = 0;
	res = check_walls(row, col, map);
	res = count_elements(row, col, map);
	// printf("res %d\n", res);
	return (res);
}

void parse_map(t_map *map, char *map_filename)
{
	int	map_file;

	map_file = open(map_filename, O_RDONLY);
	if (map_file < 0)
		ft_error("Failed to open map file");
	map->valid = map_size_valid(map_file, map);
	close(map_file);
	if (!map->valid)
		ft_error("invalid map format\n");
	get_map_elements(map, map_filename);
	map->valid = check_map_elements(map);
}
