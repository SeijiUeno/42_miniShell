/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:13:07 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 19:06:45 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Function to expand until a specific character
char	*expand_until_char(const char *input_str, int *index, char stop_char)
{
	int	start_index;
	int	len;

	start_index = *index;
	len = 0;
	while (input_str[*index] && input_str[*index] != stop_char
		&& input_str[*index] != '$')
	{
		(*index)++;
		len++;
	}
	return (ft_substr(input_str, start_index, len));
}

// Function to expand words outside quotes
char	*expand_word(const char *input_str, int *index)
{
	int	start_index;
	int	len;

	start_index = *index;
	len = 0;
	while (input_str[*index] && !strchr(QUOTES, input_str[*index])
		&& input_str[*index] != '$')
	{
		(*index)++;
		len++;
	}
	return (ft_substr(input_str, start_index, len));
}

// Static function to get the environment variable value
static char	*env_get_value_from_envp(const char *env_entry, int var_len)
{
	int	start_index;

	start_index = var_len;
	if (env_entry[start_index] == '=')
		start_index++;
	return (strdup(&env_entry[start_index]));
}

char	*expand_env(const char *var_name, char **envp)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = strlen(var_name);
	while (envp[i])
	{
		if (strncmp(var_name, envp[i], var_len) == 0 && (envp[i][var_len] == '='
			|| envp[i][var_len] == '\0'))
		{
			return (env_get_value_from_envp(envp[i], var_len));
		}
		i++;
	}
	return (strdup(""));
}
