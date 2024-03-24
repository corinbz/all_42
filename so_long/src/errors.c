/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:13:55 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/24 17:46:59 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void ft_error(char *error_txt)
{
	ft_putstr_fd(error_txt, 2);
	mlx_strerror(mlx_errno);
	exit(EXIT_FAILURE);
}