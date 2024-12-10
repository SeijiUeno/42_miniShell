/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:18:11 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 18:56:55 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.c";

void close_all_pipes(int *pipes, int total_fds) {
    for (int i = 0; i < total_fds; i++)
        close(pipes[i]);
}

int create_pipes(int *pipes, int command_count) {
    int total_fds = (command_count - 1) * 2;
    for (int i = 0; i < total_fds; i += 2) {
        if (pipe(&pipes[i]) < 0) {
            perror("pipe");
            close_all_pipes(pipes, i);
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}
