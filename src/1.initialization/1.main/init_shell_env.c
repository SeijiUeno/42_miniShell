/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:35:51 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:30:15 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static void	initialize_signals(void)
{
	signal_setup();
}

static char	**initialize_env(void)
{
	extern char	**environ;
	char		**env;

	env = get_env(environ);
	if (!env)
	{
		perror("Failed to initialize");
		exit(EXIT_FAILURE);
	}
	return (env);
}

static int	backup_standard_fds(int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdin_backup < 0 || *stdout_backup < 0)
	{
		perror("Failed to backup file descriptors");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	shell_initialize(t_ms *minishell)
{
	ft_bzero(minishell, sizeof(t_ms));
	minishell->envp = initialize_env();
	minishell->path = get_paths(minishell->envp);
	if (backup_standard_fds(&minishell->stdin_backup, &minishell->stdout_backup)
		!= EXIT_SUCCESS)
	{
		clear_al(minishell);
		exit(EXIT_FAILURE);
	}
	initialize_signals();
}
