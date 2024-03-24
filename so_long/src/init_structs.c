/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:53:53 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/24 19:01:02 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

t_map create_map(void)
{
	t_map	map;

	map.width = 0;
	map.height = 0;
	map.valid = true;
	map.cell_value = ft_calloc(20, sizeof(char *));
	return (map);
}
void get_map_elements(t_map *map)
{
	int map_file = open("maps/map.ber", O_RDONLY);
	if (map_file < 0)
		ft_error("Failed to open map file");
	char *line;
	int rows = 0;
	while((line = get_next_line(map_file)))
	{
		map->cell_value[rows] = ft_strdup(line);
		// printf("    %d is   %s", rows, map->cell_value[rows]);
		free(line);
		rows++;
	}
	close(map_file);
}

void init_game_struct	(t_game *game)
{
	game->player_pos = (t_player_pos){0};
	game->map = (t_map){0};
	game->screen = (t_screen){0};
	game->imgs.image_size = 64;
}

void start_game	(t_game *game)
{
	//map
	game->map = create_map();
	parse_map(&game->map);
	get_map_elements(&game->map);
	game->screen.width = (game->map.width) * game->imgs.image_size;
	game->screen.height = game->map.height * game->imgs.image_size;
	//imgs
	if (!(game->mlx = mlx_init(game->screen.width, game->screen.height, "Hungry frog", true)))
		ft_putstr_fd("Failed to init mlx (main)\n", 2);
	game->imgs = create_imgs(game->mlx, game->imgs);
}


