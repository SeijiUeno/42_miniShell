/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:55:55 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 14:49:57 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char	*var_validate_name(char *variable)
{
	int	index;

	// Check if the input is valid and starts with a letter or underscore
	if (!variable || !(ft_isalpha(variable[0]) || variable[0] == '_'))
		return (variable);
	// Validate remaining characters up to '='
	index = 1;
	while (variable[index] && variable[index] != '=')
	{
		if (!ft_isalnum(variable[index]) && variable[index] != '_')
			return (variable);
		index++;
	}
	// If all checks pass, return NULL (valid variable)
	return (NULL);
}

char	*get_single_env(char *name, char **environment)
{
	int	index;
	int	name_length;

	if (!name || !environment)
		return (NULL);
	name_length = ft_strlen(name);
	// Search for the environment variable in the list
	index = 0;
	while (environment[index])
	{
		if (!ft_strncmp(name, environment[index], name_length)
			&& (environment[index][name_length] == '='
			|| environment[index][name_length] == '\0'))
		{
			// Return a duplicate of the matching variable
			return (ft_strdup(environment[index]));
		}
		index++;
	}
	// Return NULL if not found
	return (NULL);
}
