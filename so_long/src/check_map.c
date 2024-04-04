/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:41:30 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/04 14:06:45 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"


static void get_and_check_map_width(int fd, t_map *map)
{
	char *line;
	line = get_next_line(fd);
	size_t len;

	len = ft_line_len(line);
	map->width = len;
	free(line);
	while((line = get_next_line(fd)))
	{
		len = ft_line_len(line);
		if (len != map->width)
		{
			map->valid = false;
			return(free(line));
		}
		free(line);
	}
	free(line);
}

static void get_map_height(int fd, t_map *map)
{
	char *line;
	size_t height;

	height = 0;
	while((line = get_next_line(fd)))
	{		
		height++;
		free(line);
	}
	map->height = height;
	
}
static bool	check_walls(size_t row, size_t col, int map_fd, t_map *map)
{
	char	*line;

	line = get_next_line(map_fd);
	while ((line))
	{
		if (row == 0 || row == map->height - 1)
		{
			while (col < map->width)
			{
				if (line[col] != '1')
					return (free(line), false);
				col++;
			}
		}
		if (line[0] != '1' || line[map->width -1] != '1')
			return (free(line), false);
		col = 0;
		row++;
		free(line);
		line = get_next_line(map_fd);
	}
	return (free(line), true);
}

static bool count_elements(size_t row, size_t col, int map_fd, t_map *map)
{
	size_t	player;
	size_t	exit;
	size_t	collectible;
	char	*line;
	
	player = 0;
	exit = 0;
	collectible = 0;
	line = get_next_line(map_fd);
	while(line)
	{
		while(col < map->width)
		{
			if (line[col] == 'P')
				player++;
			else if (line[col] == 'C')
				collectible++;
			else if (line[col] == 'E')
				exit++;
			else if (line[col] == '1' || line[col] == '0')
			{
				col++;
				continue;
			}
			else
				return (free(line), false);
			col++;
		}
		col = 0;
		row++;
		free(line);
		line = get_next_line(map_fd);
	}
	if (player != 1 || exit != 1 || collectible == 0)
		return (free(line), false);
	return(free(line), true);
}


static bool check_map_elements(t_map *map, char *map_filename)
{
	bool	res;
	size_t	row;
	size_t	col;
	int		map_fd;

	res = true;
	row = 0;
	col = 0;
	map_fd = open(map_filename, O_RDONLY);
	if (map_fd < 0)
		ft_error("Failed to open map file");
	res = check_walls(row, col, map_fd, map);
	close(map_fd);
	map_fd = open(map_filename, O_RDONLY);
	if (map_fd < 0)
		ft_error("Failed to open map file");
	res = count_elements(row, col, map_fd, map);
	close(map_fd);
	// printf("res %d\n", res);
	return (res);
}
	
void parse_map(t_map *map, char *map_filename)
{
	int map_file = open(map_filename, O_RDONLY);
	if (map_file < 0)
		ft_error("Failed to open map file");
	get_map_height(map_file, map);
	close(map_file);
	map_file = open(map_filename, O_RDONLY);
	if (map_file < 0)
		ft_error("Failed to open map file");
	get_and_check_map_width(map_file, map);
	close(map_file);
	map->valid = check_map_elements(map, map_filename);
}
