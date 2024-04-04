/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:53:53 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/04 12:30:59 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

t_map create_map(void)
{
	t_map	map;

	map.width = 0;
	map.height = 0;
	map.valid = true;
	return (map);
}
void	get_map_elements(t_map *map, char *map_filename)
{
	map->cell_value = ft_calloc(map->height + 1, sizeof(char *));
	int map_file = open(map_filename, O_RDONLY);
	if (map_file < 0)
		ft_error("Failed to open map file\n");
	char *line;
	int rows = 0;
	while((line = get_next_line(map_file)))
	{
		map->cell_value[rows] = ft_strdup(line);
		free(line);
		rows++;
	}
	close(map_file);
}

void init_game_struct(t_game *game, char* map_name)
{
	game->player_pos = (t_player_pos){0};
	game->map = (t_map){0};
	game->screen = (t_screen){0};
	game->imgs.image_size = 64;
	game->count_collect = 0;
	game->moves = 0;
	game->map_name = ft_strjoin("maps/", map_name);
	if(!game->map_name)
		return(ft_putstr_fd("failed to join maps/\n", 2), exit(EXIT_FAILURE));
}

void start_game	(t_game *game)
{
	game->map = create_map();
	parse_map(&game->map, game->map_name);
	if(!game->map.valid)
	{
		return(ft_putstr_fd("map invalid\n", 2), free(game->map_name), exit(EXIT_FAILURE));
	}
	get_map_elements(&game->map, game->map_name);
	game->screen.width = (game->map.width) * game->imgs.image_size;
	game->screen.height = game->map.height * game->imgs.image_size;
	if (!(game->mlx = mlx_init(game->screen.width,
				game->screen.height, "Hungry frog", true)))
		ft_putstr_fd("Failed to init mlx (main)\n", 2);
	game->imgs = create_imgs(game->mlx, game->imgs);
}
