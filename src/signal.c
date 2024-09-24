/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:23 by sueno-te          #+#    #+#             */
/*   Updated: 2024/09/24 17:19:45 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void handle_sigint(int sig) {

    if (sig)
    {
     // Handle Ctrl-C (SIGINT) signal: simply print a new prompt on a new line
    printf("\n");
    rl_on_new_line(); // Tell readline a new line was printed
    rl_replace_line("", 0); // Clear the current input line
    rl_redisplay(); // Redisplay the prompt
    }
}

void signal_init(void)
{
    // Set up signal handling for Ctrl-C
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN); // Ignore Ctrl-\ (SIGQUIT)
}