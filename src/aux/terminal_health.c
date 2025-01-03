/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_health.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:30:07 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/02 17:38:56 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	termios_save(struct termios *original_term)
{
	if (tcgetattr(STDIN_FILENO, original_term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
}

void	termios_restore(const struct termios *original)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, original) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void	prompt_clear(t_ms *minishell)
{
	minishell->input = NULL;
	minishell->tokens = NULL;
	minishell->tree_cmd = NULL;
	minishell->pid_list = NULL;
}

void	clear_al(t_ms *minishell)
{
	if (!minishell)
		return ;
	prompt_clear(minishell);
	if (minishell->stdin_backup >= 0)
		close(minishell->stdin_backup);
	if (minishell->stdout_backup >= 0)
		close(minishell->stdout_backup);
	rl_clear_history();
	gc_cleanup();
}
