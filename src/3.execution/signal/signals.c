/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:23 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/03 15:37:21 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

volatile sig_atomic_t	g_in_subprocess = 0;

int	status_filter(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	status_control(int status)
{
	static int	status_backup;

	if (status == -42)
		return (status_backup);
	status_backup = status;
	return (status_backup);
}

void	signal_handle_execution(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		status_control(signum + 128);
	}
	else if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		status_control(signum + 128);
	}
}

void	signal_handle(int signum)
{
	if (signum == SIGINT)
	{
		if (!g_in_subprocess)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		status_control(signum + 128);
	}
	else if (signum == SIGQUIT)
	{
		if (!g_in_subprocess)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}



void	signal_setup(void)
{
	if (signal(SIGINT, &signal_handle) == SIG_ERR)
		perror("Error setting SIGINT handler");
	if (signal(SIGQUIT, &signal_handle) == SIG_ERR)
		perror("Error setting SIGQUIT handler");
}
