/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:46:01 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 11:06:36 by sueno-te         ###   ########.fr       */
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
