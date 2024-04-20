/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:41:30 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/20 16:09:00 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static bool	map_size_valid(t_map *map)
{
	size_t	len;
	size_t	i;

	i = 1;
	len = ft_line_len(map->cell_value[0]);
	map->width = len;
	while(i < map->height)
	{
		if(ft_line_len(map->cell_value[i]) != len)
			return (false);
		i++;
	}
	return (true);
}

static bool	check_walls(size_t row, size_t col, t_map *map)
{
	// printf("width %zu height %zu\n", map->width, map->height);
	while (row < map->height)
	{
		if (col == 0 || col == map->width - 1)
		{
			if ((map->cell_value[row][col]) != '1')
				return (false);
		}
		else
		{
			if (row == 0 || row == map->height -1)
			{
				if ((map->cell_value[row][col]) != '1')
				{
					// printf("x %zu y %zu\n",row,col);
					return (false);
				}
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
				return (false);
			col++;
		}
		row++;
	}
	return (check_elements_count(&count));
}

static	bool check_map_elements(t_map *map)
{
	bool	res;
	size_t	row;
	size_t	col;

	res = true;
	row = 0;
	col = 0;
	res = map_size_valid(map);
	res = check_walls(row, col, map);
	res = count_elements(row, col, map);
	return (res);
}
static void get_rows_size(t_map *map, char *map_filename)
{
	int		map_fd;
	char	*line;
	size_t	rows;

	rows = 0;
	map_fd = open(map_filename, O_RDONLY);
	if (map_fd < 0)
		ft_error("Error: Failed to open map file\n");
	line = get_next_line(map_fd);
	while (line)
	{
		rows++;
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	map->height = rows;
}

int	parse_map(t_map *map, char *map_filename)
{
	get_rows_size(map, map_filename);
	get_map_elements(map, map_filename);
	map->valid = check_map_elements(map);
	if(!map->valid)
		return (1);
	return (0);
}


// void ft_check(char **map)
// {
// 	int width;
// 	int y;
// 	int x;

// 	width = ft_line_len;
// 	x = 0;
// 	y = 0;
// 	while(map[y][0] != '\0')
// 	{
// 		while(map[y][x] != '\n')
// 			x++;
// 		if (x != width)
// 			return (true);
// 		x = 0;
// 	}
// }