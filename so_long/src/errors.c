/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:13:55 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/19 17:25:55 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	ft_error(char *error_txt)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_txt, 2);
}
