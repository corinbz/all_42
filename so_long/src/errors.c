/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:13:55 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/05 11:36:29 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void ft_error(char *error_txt)
{
	ft_putstr_fd(error_txt, 2);
	exit(EXIT_FAILURE);
}