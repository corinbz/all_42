/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:53:53 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/09 12:47:28 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_graphics	create_graphics(mlx_t *mlx)
{
	t_graphics	assets;

	mlx_texture_t *player = mlx_load_png("img/player.png");
	assets.player = mlx_texture_to_image(mlx, player);
	// mlx_texture_destroy(player);
	return (assets);
}

