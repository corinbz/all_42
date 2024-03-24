/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 08:16:29 by corin             #+#    #+#             */
/*   Updated: 2024/03/24 11:01:40 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

//game = (t_game){0}; --INIT ALL MEMBERS TO 0;
int32_t main(void)
{
	t_game	game;
	
	init_game_struct(&game);
	start_game(&game);
	if(game.map.valid)
		render_images(game.mlx, game.graphics, game.map);
	mlx_key_hook(game.mlx, &ft_keyhooks, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}