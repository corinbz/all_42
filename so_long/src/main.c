/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 08:16:29 by corin             #+#    #+#             */
/*   Updated: 2024/04/20 16:37:32 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

//game = (t_game){0}; --INIT ALL MEMBERS TO 0;

static bool	valid_input(int ac, char *map, char *extension)
{
	size_t	map_len;

	if (ac != 2)
		return (false);
	map_len = ft_strlen(map);
	if (ft_strncmp(map + map_len - 4, extension, 4))
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (!valid_input(ac, av[1], ".ber"))
		return (ft_error("Invalid map input file\n"), EXIT_FAILURE);
	init_game_struct(&game, av[1]);
	start_game(&game);
	if (game.map.valid)
		render_images(&game);
	mlx_key_hook(game.mlx, &ft_keyhooks, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_game(&game);
	return (EXIT_SUCCESS);
}
