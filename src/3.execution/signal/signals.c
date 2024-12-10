/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:23 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 19:41:35 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	filter_status(int status)
{
	if (control_status(STATUS_GET) && (status == STATUS_CTRL_C || status == STATUS_QUIT))
		status = control_status(STATUS_GET);
	else if (status > STATUS_MAX)
		status = (status >> 8) & 0xff; // Extract signal code
	return (status);
}

int	control_status(int status)
{
	static int	status_backup;

	// Retrieve the current status if STATUS_GET is passed
	if (status == STATUS_GET)
		return (status_backup);
	// Update the status_backup and return it
	status_backup = status;
	return (status_backup);
}


void	handle_signal_exec(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT)
	{
		if (signum == SIGQUIT)
			ft_putstr_fd("Quit: 3", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		control_status(signum + 128);
	}
}

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
		rl_redisplay();
		control_status(signum + 128);
	}
}

void	prepare_signals(void)
{
	// Handle Ctrl+C with custom handler
	if (signal(SIGINT, &handle_signal) == SIG_ERR)
    	perror("Error setting SIGINT handler");

	// Ignore Ctrl+\ (SIGQUIT) to prevent core dumps
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
   		perror("Error setting SIGINT handler");

}
