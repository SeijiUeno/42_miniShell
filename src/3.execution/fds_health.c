/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_health.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:16:52 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 18:50:40 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	reset_fds(t_minishell *minishell)
{
	if (!minishell)
	{
		ft_putendl_fd("ERROR: invalid minishell structure\n", STDIN_FILENO);
		return;
	}

	// Restore standard input and output
	if ((dup2(minishell->stdin_backup, STDIN_FILENO) < 0)
		|| (dup2(minishell->stdout_backup, STDOUT_FILENO) < 0))
	{
		perror("dup2");
		return;
	}
}