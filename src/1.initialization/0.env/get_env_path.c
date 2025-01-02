/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:06:50 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:24:11 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char	*find_envir_variable(char *name, char **envir)
{
	int	index;
	int	name_length;

	if (!name || !envir)
		return (NULL);
	name_length = ft_strlen(name);
	index = 0;
	while (envir[index])
	{
		if (!ft_strncmp(name, envir[index], name_length)
			&& (envir[index][name_length] == '='
			|| envir[index][name_length] == '\0'))
		{
			return (ft_strdup(envir[index]));
		}
		index++;
	}
	return (NULL);
}

static char	*extract_value_from_entry(char *full_variable_entry)
{
	char	*value_start;

	value_start = ft_strchr(full_variable_entry, '=');
	if (!value_start)
		return (NULL);
	return (ft_strdup(value_start + 1));
}

char	*env_get_value(char *variable_name, char **envir)
{
	char	*full_variable_entry;
	char	*value;

	if (!variable_name || !envir)
		return (NULL);
	full_variable_entry = find_envir_variable(variable_name, envir);
	if (!full_variable_entry)
		return (NULL);
	value = extract_value_from_entry(full_variable_entry);
	gc_deallocate(full_variable_entry);
	return (value);
}
