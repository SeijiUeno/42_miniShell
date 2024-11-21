/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:16:00 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/21 14:41:43 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h> // For STDOUT_FILENO and getcwd
#include <stdlib.h> // For EXIT_FAILURE and EXIT_SUCCESS
#include "../garbage_collector/garbage_collector.h"
#include "buildins.h"

char *malloc_pwd(void)
{
    char    *buffer;
    char    *wd;
    size_t  chars;
    size_t  max_limit;

    chars = 1024;
    max_limit = PATH_MAX * 8;

    buffer = gc_allocate(chars * sizeof(char));
    if (!buffer)
        return (NULL); 

    while (1)
    {
        errno = 0;
        wd = getcwd(buffer, chars);
        if (wd)
            return (buffer);

        if (errno != ERANGE)
        {
            // An error occurred that is not due to buffer size
            perror("getcwd error");
            gc_deallocate(buffer);
            return NULL;
        }
        gc_deallocate(buffer);
        chars *= 2;
        if (chars > max_limit)
        {
            fprintf(stderr, "Error: Exceeded maximum buffer size for getcwd.\n");
            return NULL;
        }

        buffer = gc_allocate(chars * sizeof(char));
        if (!buffer)
            return NULL; // Allocation failed
    }

    // Should not reach here
    return NULL;
}

int pwd(const char **args)
{
    char *cwd;

    (void)args;

    cwd = malloc_pwd();
    if (!cwd)
    {
        fprintf(stderr, "Error: Failed to get current working directory.\n");
        return EXIT_FAILURE;
    }

    ft_putendl_fd(cwd, STDOUT_FILENO);

    // Deallocate cwd if it's no longer needed
    if (gc_deallocate(cwd) != GC_SUCCESS)
    {
        fprintf(stderr, "Warning: Failed to deallocate memory for cwd.\n");
    }

    return EXIT_SUCCESS;
}
