/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:23 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/05 18:28:50 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../../libft/includes/garbage_collector.h"

int	control_status(int status)
{
	static int	status_backup;

	if (status == -1)
		return (status_backup);
	status_backup = status;
	return (status_backup);
}

int	filter_status(int status)
{
	if (control_status(-1) && (status == 2 || status == 3))
		status = control_status(-1);
	else if (status > 255)
		status = (status >> 8) & 0xff;
	return (status);
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
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
