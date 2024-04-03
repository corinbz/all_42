/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 08:16:29 by corin             #+#    #+#             */
/*   Updated: 2024/04/03 17:02:34 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

//game = (t_game){0}; --INIT ALL MEMBERS TO 0;

static bool valid_input(int ac, char *map, char *extension)
{
	size_t map_len;

	if(ac != 2)
	{
		ft_putstr_fd("You need to provide a valid map file name\n", 2);
		return(false);
	}
	map_len = ft_strlen(map);
	if(ft_strncmp(map + map_len - 4, extension, 4))
	{
		ft_putstr_fd("Filename is not valid\n", 2);
		return (false);
	}
	return (true);
} 
int32_t main(int ac, char **av)
{
	t_game	game;
	if(!valid_input(ac, av[1], ".ber"))
		return(EXIT_FAILURE);
	
	init_game_struct(&game, av[1]);
	start_game(&game);
	if(game.map.valid)
		render_images(&game);
	mlx_key_hook(game.mlx, &ft_keyhooks, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	mlx_terminate(game.mlx);
	// free_game(&game);
	return (EXIT_SUCCESS);
}
