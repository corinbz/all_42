/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:53:53 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/28 10:34:17 by ccraciun         ###   ########.fr       */
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

bool	get_map_elements(t_map *map, char *map_filename)
{
	int		map_fd;
	char	*line;
	int		rows;

	rows = 0;
	map->cell_value = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->cell_value)
		return (ft_error("Malloc failed(cell_value)\n"), false);
	map->cell_value[map->height] = NULL;
	map_fd = open(map_filename, O_RDONLY);
	if (map_fd < 0)
		return (ft_error("Error: Failed to open map file\n"), false);
	line = get_next_line(map_fd);
	while (line)
	{
		map->cell_value[rows] = ft_strdup(line);
		if (!map->cell_value[rows])
			return (free(line), false);
		free(line);
		rows++;
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (true);
}

void	init_game_struct(t_game *game, char *map_name)
{
	int	fd;

	game->player_pos = (t_player_pos){0};
	game->map = (t_map){0};
	game->screen = (t_screen){0};
	game->imgs.image_size = 64;
	game->count_collect = 0;
	game->moves = 0;
	game->map_name = ft_strjoin("maps/", map_name);
	if (!game->map_name)
		return (ft_error("Failed to join maps/\n"), exit(1));
	fd = open(game->map_name, O_RDONLY);
	if (fd < 0)
		return (ft_error("Map file not accesible\n"),
			free(game->map_name), exit(1));
}

static void	get_player_pos(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	while (x < game->map.height)
	{
		while (y < game->map.width)
		{
			if (game->map.cell_value[x][y] == 'P')
			{
				game->player_pos.x = x;
				game->player_pos.y = y;
				return ;
			}
			y++;
		}
		y = 0;
		x++;
	}
}

void	start_game(t_game *game)
{
	game->map = create_map();
	if (!parse_map(game))
		return (free_game(game), exit(1));
	if (!game->map.valid)
	{
		ft_error("Map invalid\n");
		return (free_game(game), exit(1));
	}
	get_player_pos(game);
	game->map.valid = collectibles_accesible(game);
	if (!game->map.valid)
	{
		return (free_game(game), exit(1));
	}
	game->screen.width = (game->map.width) * game->imgs.image_size;
	game->screen.height = game->map.height * game->imgs.image_size;
	game->mlx = mlx_init(game->screen.width, game->screen.height,
			"Hungry frog", true);
	if (!game->mlx)
		ft_error("Failed to init mlx (main)\n");
	game->map.valid = create_imgs(game->mlx, game->imgs);
	printf("map->valid is %d\n", game->map.valid);
}
