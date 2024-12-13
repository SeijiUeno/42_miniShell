/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:18:11 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 19:40:11 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void pipe_close_all(int *pipes, int total_fds) {
    for (int i = 0; i < total_fds; i++)
        close(pipes[i]);
}

int pipe_create(int *pipes, int command_count) {
    int total_fds = (command_count - 1) * 2;
    for (int i = 0; i < total_fds; i += 2) {
        if (pipe(&pipes[i]) < 0) {
            perror("pipe");
            pipe_close_all(pipes, i);
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}
