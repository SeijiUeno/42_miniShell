/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:23 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 19:25:33 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	status_filter(int status)
{
	if (status_control(STATUS_GET) && (status == STATUS_CTRL_C || status == STATUS_QUIT))
		status = status_control(STATUS_GET);
	else if (status > STATUS_MAX)
		status = (status >> 8) & 0xff; // Extract signal code
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
	if (signum == SIGINT || signum == SIGQUIT)
	{
		if (signum == SIGQUIT)
			ft_putstr_fd("Quit: 3", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		status_control(signum + 128);
	}
}

void	signal_handle(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
		rl_redisplay();
		status_control(signum + 128);
	}
}

void	signal_setup(void)
{
	// Handle Ctrl+C with custom handler
	if (signal(SIGINT, &signal_handle) == SIG_ERR)
    	perror("Error setting SIGINT handler");

	// Ignore Ctrl+\ (SIGQUIT) to prevent core dumps
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
   		perror("Error setting SIGINT handler");

}
