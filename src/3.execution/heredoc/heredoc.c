/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:26:58 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 00:49:55 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Handles the main heredoc logic (file creation, reading, and cleanup)
int heredoc(char **str, int index) {
    char *filename;
    int fd;
    int status;

    filename = heredoc_generate_name(index);
    if (!filename) {
        return EXIT_FAILURE;
    }

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        ft_putstr_fd("Error: Failed to open heredoc file: ", STDERR_FILENO);
        ft_putstr_fd(filename, STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        free(filename);
        return EXIT_FAILURE;
    }

    status = heredoc_read(*str, fd);
    close(fd);

    if (status != 0) {
        free(filename);
        return status;
    }

    free(*str);
    *str = filename;

    return 0;
}
