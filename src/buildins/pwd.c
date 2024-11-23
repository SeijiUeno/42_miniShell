/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:16:00 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/22 20:36:46 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>
#include <unistd.h> // For STDOUT_FILENO and getcwd
#include <stdlib.h> // For EXIT_FAILURE and EXIT_SUCCESS
#include "../../libft/includes/garbage_collector.h"
#include "buildins.h"
#include "../shell.h"

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
            ft_putendl_fd("getcwd error", STDERR_FILENO);
            gc_deallocate(buffer);
            return (NULL);
        }
        gc_deallocate(buffer);
        chars *= 2;
        if (chars > max_limit)
        {
            ft_putendl_fd("Error: Exceeded maximum buffer size for getcwd.\n", STDERR_FILENO);
            return (NULL);
        }

        buffer = gc_allocate(chars * sizeof(char));
        if (!buffer)
            return (NULL);
    }
    return (NULL);
}

int pwd(const char **args)
{
    char *cwd;
    
    (void)args;
    cwd = malloc_pwd();
    if (!cwd)
    {
        ft_putendl_fd("Error: Failed to get current working directory.\n", STDERR_FILENO);
        return EXIT_FAILURE;
    }

    ft_putendl_fd(cwd, STDOUT_FILENO);

    // Deallocate cwd if it's no longer needed
    if (gc_deallocate(cwd) != GC_SUCCESS)
    {
        ft_putendl_fd("Warning: Failed to deallocate memory for cwd.\n", STDERR_FILENO);
    }

    return (EXIT_SUCCESS);
}
