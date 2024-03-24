/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:41:30 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/24 10:16:25 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"


static void get_and_check_map_width(int fd, t_map *map)
{
	char *line;
	line = get_next_line(fd);
	size_t len;

	len = ft_line_len(line);
	if (len > map->width)
		map->width = len;
	while((line = get_next_line(fd)))
	{
		len = ft_line_len(line);
		if (len != map->width)
		{
			map->valid = false;
			return ;
		}
		free(line);
	}
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

static bool check_map_elements(t_map *map)
{
	size_t row;
	size_t col;
	size_t player;
	size_t exit;
	size_t collectible;
	
	row = 0;
	col = 0;
	player = 0;
	exit = 0;
	collectible = 0;
	
	int map_file = open("maps/map.ber", O_RDONLY);
	if (map_file < 0)
		ft_error("Failed to open map file");
	char *line;
	// printf("width %zu\n", map->width);
	while((line = get_next_line(map_file)))
	{
		if (row == 0)
		{
			while(col < map->width)
			{
				if (line[col] != '1')
				{
					return (false);
				}
				col++;
			}
			col = 0;
			row++;
		}
		while(col < map->width)
		{			
			if (line[0] != '1' || line[map->width -1] != '1')
			{
				return (false);
			}
			else if (line[col] == 'P')
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
			{
				return (false);
			}
			col++;
		}
		col = 0;
		row++;
	}
	if (player != 1 || exit != 1 || collectible == 0)
		return (false);
	return (true);
}
	
void parse_map(t_map *map)
{
	int map_file = open("maps/map.ber", O_RDONLY);
	if (map_file < 0)
		ft_error("Failed to open map file");
	get_map_height(map_file, map);
	close(map_file);
	map_file = open("maps/map.ber", O_RDONLY);
	if (map_file < 0)
		ft_error("Failed to open map file");
	get_and_check_map_width(map_file, map);
	close(map_file);
	map->valid = check_map_elements(map);
	printf("map read succes and %d\n", map->valid);
}
