/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:53:53 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/14 18:30:12 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

t_map	create_map(void)
{
	t_map	map;

	map.width = 0;
	map.height = 0;
	map.valid = true;
	return (map);
}

//maybe check maloc protections here
void	get_map_elements(t_map *map, char *map_filename)
{
	int		map_fd;
	char	*line;
	int		rows;

	rows = 0;
	map->cell_value = ft_calloc(map->height + 1, sizeof(char *));
	map->visited_cell = ft_calloc(map->height + 1, sizeof(char *));
	map_fd = open(map_filename, O_RDONLY);
	if (map_fd < 0)
		ft_error("Error: Failed to open map file\n");
	line = get_next_line(map_fd);
	while (line)
	{
		map->cell_value[rows] = ft_strdup(line);
		if (!map->cell_value[rows])
		{
			ft_free_2d(map->cell_value);
		}
		free(line);
		rows++;
		line = get_next_line(map_fd);
	}
	close(map_fd);
}

void	init_game_struct(t_game *game, char *map_name)
{
	game->player_pos = (t_player_pos){0};
	game->map = (t_map){0};
	game->screen = (t_screen){0};
	game->imgs.image_size = 64;
	game->count_collect = 0;
	game->moves = 0;
	game->map_name = ft_strjoin("maps/", map_name);
	if (!game->map_name)
		return (ft_putstr_fd("failed to join maps/\n", 2), exit(EXIT_FAILURE));
}

void	start_game(t_game *game)
{
	game->map = create_map();
	parse_map(&game->map, game->map_name);
	if (!game->map.valid)
	{
		ft_putstr_fd("map invalid\n", 2);
		return (free(game->map_name), exit(EXIT_FAILURE));
	}
	get_map_elements(&game->map, game->map_name);
	game->screen.width = (game->map.width) * game->imgs.image_size;
	game->screen.height = game->map.height * game->imgs.image_size;
	game->mlx = mlx_init(game->screen.width, game->screen.height, "Hungry frog", true);
	if (!game->mlx)
		ft_putstr_fd("Failed to init mlx (main)\n", 2);
	game->imgs = create_imgs(game->mlx, game->imgs);
}
