/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_health.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:16:52 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 19:24:37 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	fds_reset(t_minishell *minishell)
{
	if (!minishell)
	{
		ft_putendl_fd("ERROR: invalid minishell structure\n", STDIN_FILENO);
		return ;
	}
	// Restore standard input and output
	if ((dup2(minishell->stdin_backup, STDIN_FILENO) < 0)
		|| (dup2(minishell->stdout_backup, STDOUT_FILENO) < 0))
	{
		perror("dup2");
		return ;
	}
}
