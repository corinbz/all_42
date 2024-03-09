/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:41:30 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/09 15:33:02 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void get_map_width(char *line, t_map *map)
{
	size_t len;

	len = strlen(line);
	if (len > map->width)
		map->width = len;
}

void get_map_height(int fd, t_map *map)
{
	char *line;
	size_t height;

	height = 0;
	while ((line = get_next_line(fd)) > 0)
	{
		height++;
		free(line);
	}
	map->height = height;
}

void read_map(int fd, t_map *map)

{
	char *line;
	line = get_next_line(fd);
	if (!line)
		ft_error("Failed to read map");
	get_map_width(line, map);
	while ((line = get_next_line(fd)) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
}