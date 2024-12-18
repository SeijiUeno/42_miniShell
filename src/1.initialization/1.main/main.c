/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:16:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 14:06:22 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static void	cleanup_minishell(t_minishell *minishell)
{
	free_all(minishell);
	if (minishell->stdin_backup >= 0)
		close(minishell->stdin_backup);
	if (minishell->stdout_backup >= 0)
		close(minishell->stdout_backup);
}

int	main(void)
{
	t_minishell	minishell;

	shell_initialize(&minishell);
	shell_loop(&minishell);
	cleanup_minishell(&minishell);
	return (EXIT_SUCCESS);
}
