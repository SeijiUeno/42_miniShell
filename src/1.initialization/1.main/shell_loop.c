/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:36:28 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/06 14:51:14 by sueno-te         ###   ########.fr       */
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
	int	status;

	if (!minishell->input || minishell->input[0] == '\0')
		return ;
	status = build_commands(minishell);
	if (status == EXIT_SUCCESS)
		execute(minishell);
	else
		status_control(status);
	return ;
}

static void	cleanup_iteration(t_ms *minishell)
{
	prompt_clear(minishell);
	fds_reset(minishell);
	return ;
}

void	shell_loop(t_ms *minishell)
{
	static struct termios	original_term;

	termios_save(&original_term);
	while (42)
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
