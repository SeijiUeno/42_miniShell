/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:06:50 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 19:28:52 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char *find_environment_variable(char *name, char **environment)
{
    int index;
    int name_length;

    if (!name || !environment)
        return NULL;

    name_length = ft_strlen(name);

    for (index = 0; environment[index]; index++)
    {
        if (!ft_strncmp(name, environment[index], name_length) &&
            (environment[index][name_length] == '=' || environment[index][name_length] == '\0'))
        {
            return ft_strdup(environment[index]);
        }
    }

    return NULL;
}

static char *extract_value_from_entry(char *full_variable_entry)
{
    char *value_start;

    value_start = ft_strchr(full_variable_entry, '=');
    if (!value_start)
        return (NULL);

    return (ft_strdup(value_start + 1));
}

char *env_get_value(char *variable_name, char **environment)
{
    char *full_variable_entry;
    char *value;

    if (!variable_name || !environment)
        return (NULL);

    full_variable_entry = find_environment_variable(variable_name, environment);
    if (!full_variable_entry)
        return (NULL);

    value = extract_value_from_entry(full_variable_entry);
    free(full_variable_entry);
    return (value);
}
