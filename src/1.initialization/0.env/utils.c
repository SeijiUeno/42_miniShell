/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:55:55 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:53:13 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char	*var_validate_name(char *variable)
{
	int	index;

	if (!variable || !(ft_isalpha(variable[0]) || variable[0] == '_'))
		return (variable);
	index = 1;
	while (variable[index] && variable[index] != '=')
	{
		if (!ft_isalnum(variable[index]) && variable[index] != '_')
			return (variable);
		index++;
	}
	return (NULL);
}

char	*get_single_env(char *name, char **environment)
{
	int	index;
	int	name_length;

	if (!name || !environment)
		return (NULL);
	name_length = ft_strlen(name);
	index = 0;
	while (environment[index])
	{
		if (!ft_strncmp(name, environment[index], name_length)
			&& (environment[index][name_length] == '='
			|| environment[index][name_length] == '\0'))
		{
			gc_track(environment[index]);
			return (ft_strdup(environment[index]));
		}
		index++;
	}
	return (NULL);
}
