/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:46:01 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/04 18:33:09 by sueno-te         ###   ########.fr       */
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
	status_control(status_filter(num_error));
	return (num_error);
}
