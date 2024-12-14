/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:46:01 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 19:54:51 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	error(const char *content, char *error, int num_error)
{
	if (content)
	{
		ft_putstr_fd(content, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error)
		ft_putendl_fd(error, STDERR_FILENO);
	else
		ft_putendl_fd("An error occurred", STDERR_FILENO);
	return (num_error);
}
