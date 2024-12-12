/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:46:01 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 17:31:53 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	error(const char *content, char *error, int num_error)
{
	ft_putstr_fd(content, STDERR_FILENO);
	if (error)
		ft_putendl_fd(error, STDERR_FILENO);
	else
		perror(NULL);
	return (num_error);
}