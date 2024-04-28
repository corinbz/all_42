/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:41:30 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/28 10:37:51 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static bool	map_size_valid(t_map *map)
{
	size_t	len;
	size_t	i;

	i = 1;
	len = ft_line_len(map->cell_value[0]);
	if (len > MAX_MAP_WIDTH)
		return (ft_error("Width too big\n"), false);
	map->width = len;
	while (i < map->height)
	{
		if (ft_line_len(map->cell_value[i]) != len)
			return (ft_error("Invalid row length\n"), false);
		i++;
	}
	if (map->cell_value[map->height - 1][len] == '\n')
		return (ft_error("New line on end of file\n"), false);
	return (true);
}

static bool	check_walls(size_t row, size_t col, t_map *map)
{
	while (row < map->height)
	{
		while (col < map->width)
		{
			if (col == 0 || col == map->width)
			{
				if ((map->cell_value[row][col]) != '1')
					return (ft_error("Incomplete wall\n"), false);
			}
			if (row == 0 || row == map->height - 1)
			{
				if ((map->cell_value[row][col]) != '1')
				{
					return (ft_error("Incomplete wall\n"), false);
				}
			}
			col++;
		}
		col = 0;
		row++;
	}
	return (true);
}

static bool	check_map_elements(t_map *map)
{
	bool	res;
	size_t	row;
	size_t	col;

	row = 0;
	col = 0;
	res = map_size_valid(map) && check_walls(row, col, map)
		&& count_elements(row, col, map);
	return (res);
}

static bool	get_rows_size(t_map *map, char *map_filename)
{
	int		map_fd;
	char	*line;
	size_t	rows;

	rows = 0;
	map_fd = open(map_filename, O_RDONLY);
	if (map_fd < 0)
		return (ft_error("Failed to open map file\n"), false);
	line = get_next_line(map_fd);
	while (line)
	{
		rows++;
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	if (rows > MAX_MAP_HEIGHT || rows < 3)
		return (ft_error("Map height is invalid\n"), false);
	map->height = rows;
	return (true);
}

bool	parse_map(t_game *game)
{
	if (!get_rows_size(&game->map, game->map_name))
		return (free(game->map_name), exit(1), false);
	game->map.valid = get_map_elements(&game->map, game->map_name);
	if (!game->map.valid)
		return (false);
	game->map.valid = check_map_elements(&game->map);
	if (!game->map.valid)
		return (false);
	return (true);
}
