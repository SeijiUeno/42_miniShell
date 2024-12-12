/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:53:41 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 19:00:55 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static char **allocate_environment_array(char **environment, int *count)
{
    char **new_environment;

    *count = 0;
    while (environment[*count])
        (*count)++;

    new_environment = ft_calloc(*count + 1, sizeof(char *));
    return (new_environment);
}

static char **free_environment_array(char **environment, int index)
{
    while (--index >= 0)
        free(environment[index]);
    free(environment);
    return (NULL);
}

char **get_env(char **environment)
{
    char **new_environment;
    int environment_count;
    int index;

    new_environment = allocate_environment_array(environment, &environment_count);
    if (!new_environment)
        return (NULL);

    for (index = 0; index < environment_count; index++)
    {
        new_environment[index] = ft_strdup(environment[index]);
        if (!new_environment[index])
            return free_environment_array(new_environment, index);
    }
    new_environment[environment_count] = (NULL);
    return (new_environment);
}