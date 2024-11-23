/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:23 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/22 20:38:12 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../../libft/includes/garbage_collector.h"

	/*  Handle Ctrl-C (SIGINT) 
		signal: simply print a new prompt on a new line */
static	void	handle_sigint(int sig)
{
	if (sig)
	{
		printf("\n");
		rl_on_new_line(); // Tell readline a new line was printed
		rl_replace_line("", 0); // Clear the current input line
		rl_redisplay(); // Redisplay the prompt
		gc_cleanup();
	}
}

void	signal_init(void)
{
	signal(SIGINT, handle_sigint); // Set up signal handling for Ctrl-C
	signal(SIGQUIT, SIG_IGN); // Ignore Ctrl-\ (SIGQUIT)
}
