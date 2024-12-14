/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:18:11 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 19:01:33 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	pipe_close_all(int *pipes, int total_fds)
{
	int	i;

	i = 0;
	while (i < total_fds)
	{
		close(pipes[i]);
		i++;
	}
}

int	pipe_create(int *pipes, int command_count)
{
	int	total_fds;
	int	i;

	total_fds = (command_count - 1) * 2;
	i = 0;
	while (i < total_fds)
	{
		if (pipe(&pipes[i]) < 0)
		{
			perror("pipe");
			pipe_close_all(pipes, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
