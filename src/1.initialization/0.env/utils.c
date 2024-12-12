/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:55:55 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 18:51:06 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char *validate_var_name(char *variable)
{
    int index;

    // Check if the input is valid and starts with a letter or underscore
    if (!variable || !(ft_isalpha(variable[0]) || variable[0] == '_'))
        return variable;

    // Validate remaining characters up to '='
    for (index = 1; variable[index] && variable[index] != '='; index++)
    {
        if (!ft_isalnum(variable[index]) && variable[index] != '_')
            return variable;
    }

    // If all checks pass, return NULL (valid variable)
    return NULL;
}

char *get_single_env(char *name, char **environment)
{
    int index;
    int name_length;

    if (!name || !environment)
        return NULL;

    name_length = ft_strlen(name);

    // Search for the environment variable in the list
    for (index = 0; environment[index]; index++)
    {
        if (!ft_strncmp(name, environment[index], name_length) &&
            (environment[index][name_length] == '=' || environment[index][name_length] == '\0'))
        {
            // Return a duplicate of the matching variable
            return ft_strdup(environment[index]);
        }
    }

    // Return NULL if not found
    return NULL;
}
