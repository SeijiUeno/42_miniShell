/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:36:28 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/03 15:33:22 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static char	*handle_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (input && input[0] != '\0')
		add_history(input);
	return (input);
}

static void	process_commands(t_ms *minishell)
{
	if (!minishell->input || minishell->input[0] == '\0')
		return ;
	if (build_commands(minishell) == EXIT_SUCCESS)
		execute(minishell);
}

static void	cleanup_iteration(t_ms *minishell)
{
	prompt_clear(minishell);
	fds_reset(minishell);
}

void	shell_loop(t_ms *minishell)
{
	static struct termios	original_term;

	termios_save(&original_term);
	while (1)
	{
		minishell->input = handle_input();
		minishell->status = status_control(-42);
		if (!minishell->input)
		{
			ft_putstr_fd("\nexit\n", STDOUT_FILENO);
			cleanup_iteration(minishell);
			break ;
		}
		process_commands(minishell);
		cleanup_iteration(minishell);
	}
	termios_restore(&original_term);
}
