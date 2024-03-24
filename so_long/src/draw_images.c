/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:31:37 by corin             #+#    #+#             */
/*   Updated: 2024/03/24 17:45:31 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void draw_wall(mlx_t *mlx, t_imgs imgs, size_t x_pos, size_t y_pos)
{
	if(mlx_image_to_window(mlx, imgs.wall, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
}

void draw_floor(mlx_t *mlx, t_imgs imgs, size_t x_pos, size_t y_pos)
{
	if(mlx_image_to_window(mlx, imgs.floor, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
}
void draw_exit(mlx_t *mlx, t_imgs imgs, size_t x_pos, size_t y_pos)
{
	if(mlx_image_to_window(mlx, imgs.floor, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
	if(mlx_image_to_window(mlx, imgs.exit, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
}
void draw_player(mlx_t *mlx, t_imgs imgs, size_t x_pos, size_t y_pos)
{
	if(mlx_image_to_window(mlx, imgs.floor, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
	if(mlx_image_to_window(mlx, imgs.player, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
}
void draw_collectible(mlx_t *mlx, t_imgs imgs, size_t x_pos, size_t y_pos)
{
	if(mlx_image_to_window(mlx, imgs.floor, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
	if(mlx_image_to_window(mlx, imgs.collectible, x_pos * 64, y_pos * 64) < 0)
		ft_error("Failed to draw image to window");
}