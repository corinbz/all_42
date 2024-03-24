/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 08:16:29 by corin             #+#    #+#             */
/*   Updated: 2024/03/24 20:51:46 by corin            ###   ########.fr       */
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
	{
		// printf("img size is %zu\n",game.imgs.image_size);
		render_images(&game);
	}
	// mlx_put_string(game.mlx, "YOU WON!", 300, 300);
	mlx_key_hook(game.mlx, &ft_keyhooks, &game);
	// printf("collectibles %zu\n", game.count_collect);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	// free_game(&game);
	return (EXIT_SUCCESS);
}