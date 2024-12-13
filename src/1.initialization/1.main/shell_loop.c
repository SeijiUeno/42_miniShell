/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:36:28 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 14:09:33 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static int	get_and_reset_status(void)
{
	int	current_status;

	current_status = status_control(STATUS_GET);
	status_control(0);
	return (current_status);
}

static char	*handle_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (input && input[0] != '\0') // Add input to history only if non-empty
		add_history(input);
	return (input);
}

static void	process_commands(t_minishell *minishell)
{
	if (build_commands(minishell) == EXIT_SUCCESS)
		execute(minishell);
}

static void	cleanup_iteration(t_minishell *minishell)
{
	prompt_clear(minishell);
	fds_reset(minishell); // Restore stdin and stdout
}

void	shell_loop(t_minishell *minishell)
{
	static struct termios	original_term;

	terminal_save_settings(&original_term);
	while (1)
	{
		minishell->input = handle_input();
		minishell->status = get_and_reset_status();
		if (!minishell->input) // Handle EOF (Ctrl+D)
		{
			//**************** ft_printf("BY SHELL!\n");
			break ;
		}
		process_commands(minishell);
		cleanup_iteration(minishell);
	}
	terminal_restore_settings(&original_term); // Final cleanup
}
