/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:23 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 19:25:53 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

volatile sig_atomic_t	g_in_subprocess = 0;

int	status_filter(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status)); // Normal exit with exit code
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status)); // Signal-based termination
	return (status);
}

int	status_control(int status)
{
	static int	status_backup;

	if (status == STATUS_GET)
		return (status_backup);
	status_backup = status;
	return (status_backup);
}

void	signal_handle_execution(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
			// Notify the user about SIGQUIT
		status_control(signum + 128);
	}
	else if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO); // Notify the user about SIGINT
		status_control(signum + 128);
	}
}

void	signal_handle(int signum)
{
	if (signum == SIGINT)
	{
		if (!g_in_subprocess)
		{
			ft_putstr_fd("\n", STDOUT_FILENO); // Print newline for shell prompt
			rl_replace_line("", 0);            // Clear the current line
			rl_on_new_line();                  // Start a new line for input
			rl_redisplay();                    // Redisplay the prompt
		}
		status_control(signum + 128); // Update status for signal
	}
}

void	signal_setup(void)
{
	// Handle Ctrl+C with custom handler
	if (signal(SIGINT, &signal_handle) == SIG_ERR)
		perror("Error setting SIGINT handler");
	if (signal(SIGQUIT, &signal_handle) == SIG_ERR)
		perror("Error setting SIGQUIT handler");
}
